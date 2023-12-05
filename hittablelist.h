#pragma once

#include "hittable.h"

#include <memory>
#include <vector>


class HittableList : public Hittable
{
public:
	HittableList() = default;


	void clear();
	void add(std::shared_ptr<Hittable> object);
	bool hit(const Ray& r, const Interval rayT, HitRecord& rec) const override;

private:

	std::vector<std::shared_ptr<Hittable>> m_objects;
};
