#pragma once


#include "utils.h"

#include "color.h"
#include "hittable.h"


class Camera
{
public:

	void render(const Hittable& world) const;

	Camera();

private:

	Color rayColor(const Ray& r, const Hittable& world, const int depth) const;

	Ray getRay(int i, int j) const;

	Vec3 pixelSampleSquare() const;

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

};