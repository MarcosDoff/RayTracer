#pragma once

#include "ray.h"
#include "utils.h"

class Material;

class HitRecord
{
public:
	Point3 p;
	Vec3 normal;
	double t;
	bool frontFace;
	std::shared_ptr<Material> mat;

	void setFrontNormal(const Ray& r, const Vec3& outwardNormal)
	{
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}

};

class Interval
{
public:
	Interval() : m_min(-infinity), m_max(infinity) {}
	Interval(const double min, const double max) : m_min(min), m_max(max){}

	double min() const { return m_min; } 
	double max() const { return m_max; }

	bool surround(double x) const
	{
		return m_min < x&& x < m_max;
	}

	double clamp(double x) const
	{
		if (x < m_min) return m_min;
		if (x > m_max) return m_max;

		return x;
	}

private:
	double m_min, m_max;
};

namespace Intervals
{
	const static Interval empty(infinity, -infinity);
	const static Interval universe(-infinity, infinity);
}



class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& r, const Interval rayT, HitRecord& rec) const = 0;
};
