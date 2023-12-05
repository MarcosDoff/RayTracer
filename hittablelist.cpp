#include "hittablelist.h"

void HittableList::clear()
{
	m_objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
	m_objects.push_back(object);
}

bool HittableList::hit(const Ray& r, const Interval rayT, HitRecord& rec) const
{
	HitRecord tempRec;
	bool hitAnything = false;
	auto closestSoFar = rayT.max();

	for(const auto& object : m_objects)
	{
		if (object->hit(r, Interval(rayT.min(), closestSoFar), tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}
