#pragma once

#include "utils.h"
#include "ray.h"
#include "color.h"


namespace
{
	//Schlicks approximation
	double reflectance(double cosine, double refIdx);
}


class HitRecord;

class Material
{
public:
	virtual ~Material() = default;

	virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};


class Lambertian : public Material
{
public:
	Lambertian(const Color& albedo) : m_albedo(albedo)
	{
	}

	bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	Color m_albedo;
};


class Metal : public Material
{
public:
	Metal(const Color& albedo, const double fuzz) : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1)
	{
	}

	bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	Color m_albedo;
	double m_fuzz;
};

class Dialectric : public Material
{
public:
	Dialectric(double indexOfRefraction) : m_ir(indexOfRefraction)
	{
	}

	bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	double m_ir; // index of refraction
};
