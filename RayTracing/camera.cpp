#include "camera.h"

#include <iostream>
#include <future>

#include "material.h"


Camera::Camera() : m_aspectRatio(16.0 / 9), m_imageWidth(1920), m_samplesPerPixel(100),
                   m_maxDepth(10), m_vfov(20.0), m_lookFrom(13, 2, 3), m_lookAt(0, 0, 0), m_vUp(0, 1, 0)
{
	//Image
	m_imageHeight = static_cast<int>(m_imageWidth / m_aspectRatio);
	m_imageHeight = std::max(m_imageHeight, 1);

	m_center = m_lookFrom;

	m_imageBuffer.resize(4 * m_imageHeight * m_imageWidth);

	//Camera
	const double focalLength = (m_lookFrom - m_lookAt).length();
	const auto theta = degreesToRadians(m_vfov);
	const auto h = std::tan(theta / 2);
	const double viewportHeight = 2.0 * h * focalLength;
	const double viewportWidth = viewportHeight * (static_cast<double>(m_imageWidth) / m_imageHeight);


	const auto w = unitVector(m_lookFrom - m_lookAt);
	const auto u = unitVector(cross(m_vUp, w));
	const auto v = cross(w, u);


	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	const Vec3 viewportU = viewportWidth * u;
	const Vec3 viewportV = viewportHeight * (-v);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	m_pixelDeltaU = viewportU / m_imageWidth;
	m_pixelDeltaV = viewportV / m_imageHeight;

	// Calculate the location of the upper left pixel.
	const Vec3 viewportUpperLeft = m_center - (focalLength * w) - viewportU / 2 - viewportV / 2;
	m_pixel00Loc = viewportUpperLeft + 0.5 * (m_pixelDeltaU + m_pixelDeltaV);
}

void Camera::render(const Hittable& world)
{
	std::cout << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";

	std::clog << "rendering started!!\n";

	constexpr int numOfThreads = 8;//TODO: get the number of threads automatically and go line by line

	std::vector<std::future<void>> asyncs(numOfThreads);
	const int heightOfSection = static_cast<int>(m_imageHeight / numOfThreads);
	int begin = 0;
	int end = heightOfSection;

	for (int i = 0; i < numOfThreads; ++i)
	{
		asyncs[i] = std::async(std::launch::async, &Camera::renderLines, this, &world, begin, end);
		begin = end + 1;
		end = begin + heightOfSection;
	}

	for (auto& async : asyncs)
	{
		async.wait();
	}

	for (int i = 0; i < m_imageHeight; i++)
	{
		for (int j = 0; j < m_imageWidth; j++)
		{
			int index = 4 * (j + i * m_imageWidth);
			writeColor(std::cout, m_imageBuffer[index], m_imageBuffer[index + 1], m_imageBuffer[index + 2]);
		}
	}

	std::clog << "rendering ended!!\n";
}

void Camera::renderLines(const Hittable* world, int begin, int end)
{
	if (end <= begin || begin >= m_imageHeight)
	{
		std::clog << "Error\n";
		return;
	}

	if (end > m_imageHeight - 1)
	{
		end = m_imageHeight - 1;
	}

	for (int i = begin; i <= end; i++)
	{
		for (int j = 0; j < m_imageWidth; j++)
		{
			auto pixelCenter = m_pixel00Loc + (j * m_pixelDeltaU) + (i * m_pixelDeltaV);
			auto rayDirection = pixelCenter - m_center;
			Color pixelColor(0, 0, 0);
			for (int sample = 0; sample < m_samplesPerPixel; ++sample)
			{
				Ray r = getRay(j, i);
				pixelColor += rayColor(r, *world, m_maxDepth);
			}

			insertColorInBuffer(pixelColor, m_samplesPerPixel, j, i);
		}
		std::clog << "finished line: " << i << "\n";
	}
}

Color Camera::rayColor(const Ray& r, const Hittable& world, const int depth) const
{
	if (depth <= 0)
	{
		return {0, 0, 0};
	}
	HitRecord rec;
	if (world.hit(r, Interval(0.001, infinity), rec))
	{
		Ray scattered;
		Color attenuation;
		if (rec.mat->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * rayColor(scattered, world, depth - 1);
		}
		return {0, 0, 0};
	}

	const Vec3 unitDirection = unitVector(r.direction());
	const auto a = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	//return 0.1*Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

Ray Camera::getRay(int i, int j) const
{
	const auto pixelCenter = m_pixel00Loc + (i * m_pixelDeltaU) + (j * m_pixelDeltaV);
	const auto pixelSample = pixelCenter + pixelSampleSquare();

	const auto rayOrigin = m_center;
	const auto rayDirection = pixelSample - rayOrigin;

	return {rayOrigin, rayDirection};
}

Vec3 Camera::pixelSampleSquare() const
{
	auto px = -0.5 + randomDouble();
	auto py = -0.5 + randomDouble();
	return (px * m_pixelDeltaU) + (py * m_pixelDeltaV);
}

void Camera::insertColorInBuffer(const Color& pixelColor, int samplesPerPixel, int pX, int pY)
{
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	const auto scale = 1.0 / samplesPerPixel;
	r *= scale;
	g *= scale;
	b *= scale;

	r = sqrt(r);
	g = sqrt(g);
	b = sqrt(b);

	const Interval intensity(0.0000, 0.9999);

	const int index = 4 * (pX + pY * m_imageWidth);


	std::lock_guard<std::mutex> lockGuard(m_mutex);
	m_imageBuffer[index] = static_cast<uint8_t>(256 * intensity.clamp(r));
	m_imageBuffer[index + 1] = static_cast<uint8_t>(256 * intensity.clamp(g));
	m_imageBuffer[index + 2] = static_cast<uint8_t>(256 * intensity.clamp(b));
	m_imageBuffer[index + 3] = static_cast<uint8_t>(255);
}
