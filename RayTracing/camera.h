#pragma once


#include "color.h"
#include "hittable.h"
#include <vector>
#include <mutex>

class Camera
{
public:

	Camera();

	void render(const Hittable& world);

private:

	void renderLines(const Hittable* world, int begin, int end);

	Color rayColor(const Ray& r, const Hittable& world, const int depth) const;

	Ray getRay(int i, int j) const;

	Vec3 pixelSampleSquare() const;

	void insertColorInBuffer(const Color& pixelColor, int samplesPerPixel, int pX, int pY);

private:
	double m_aspectRatio;
	int m_imageWidth;
	int m_imageHeight;
	Point3 m_center;
	Point3 m_pixel00Loc;
	Vec3 m_pixelDeltaU;
	Vec3 m_pixelDeltaV;
	int m_samplesPerPixel;
	int m_maxDepth;
	double m_vfov;
	Point3 m_lookFrom;
	Point3 m_lookAt;
	Vec3 m_vUp; //relative Up
	std::vector<uint8_t> m_imageBuffer;
	std::mutex m_mutex;
};