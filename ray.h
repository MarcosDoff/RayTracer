#pragma once
#include "vec3.h"
#include <utility>

class Ray
{
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction);

	Point3 origin() const;
	Vec3 direction() const;

	Point3 at(double t) const;

	~Ray() = default;

	Ray(const Ray& other)
		: m_origin(other.m_origin),
		m_direction(other.m_direction){}

	Ray(Ray&& other) noexcept
		: m_origin(other.m_origin),
		m_direction(other.m_direction) {}

	Ray& operator=(const Ray& other);

	Ray& operator=(Ray&& other) noexcept;

private:
	Point3 m_origin;
	Vec3 m_direction;
};
