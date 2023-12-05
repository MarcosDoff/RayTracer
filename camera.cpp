#include "camera.h"

#include <iostream>

#include "material.h"

void Camera::render(const Hittable& world) const
{
	std::cout << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";

	for (int i = 0; i < m_imageHeight; i++)
	{
		std::clog << "\rScan lines remaining: " << (m_imageHeight - i) << ' ' << std::flush;
		for (int j = 0; j < m_imageWidth; j++)
		{
			auto pixelCenter = m_pixel00Loc + (j * m_pixelDeltaU) + (i * m_pixelDeltaV);
			auto rayDirection = pixelCenter - m_center;
			Color pixelColor(0, 0, 0);
			for (int sample = 0; sample < m_samplesPerPixel; ++sample)
			{
				Ray r = getRay(j, i);
				pixelColor += rayColor(r, world, m_maxDepth);
			}

			writeColor(std::cout, pixelColor, m_samplesPerPixel);
		}
	}
}

Camera::Camera() : m_aspectRatio(16.0 / 9), m_imageWidth(1200), m_samplesPerPixel(10),
                   m_maxDepth(10), m_vfov(20.0), m_lookFrom(13, 2, 3), m_lookAt(0, 0, 0), m_vUp(0, 1, 0)
{
	//Image
	m_imageHeight = static_cast<int>(m_imageWidth / m_aspectRatio);
	m_imageHeight = std::max(m_imageHeight, 1);

	m_center = m_lookFrom;


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
