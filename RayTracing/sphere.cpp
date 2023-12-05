#include "sphere.h"

bool Sphere::hit(const Ray& r, const Interval rayT, HitRecord& rec) const
{
	const Vec3 oc = r.origin() - m_center;
	const auto dir = r.direction();
	const auto a = dir.lengthSquared();
	const auto halfB = dot(oc, r.direction());
	const auto c = oc.lengthSquared() - m_radius * m_radius;

	const auto discriminant = halfB * halfB - a * c;

	if(discriminant < 0)
	{
		return false;
	}
	const auto sqrtd = std::sqrt(discriminant);

	//find the root tha lies in the acceptable range
	auto root = (-halfB - sqrtd) / a;
	if(!rayT.surround(root))
	{
		root = (-halfB + sqrtd) / a;
		if (!rayT.surround(root))
		{
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	const Vec3 outwardNormal = (rec.p - m_center) / m_radius;
	rec.setFrontNormal(r, outwardNormal);
	rec.mat = m_mat;

	return true;
}
