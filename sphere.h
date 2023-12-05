#pragma once


#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable
{
public:
	bool hit(const Ray& r, const Interval rayT, HitRecord& rec) const override;

	Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat)
		: m_center(center),
		  m_radius(radius),
		  m_mat(std::move(mat))
	{
	}

private:
	Point3 m_center;
	double m_radius;
	std::shared_ptr<Material> m_mat;
};
