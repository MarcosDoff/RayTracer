#include "material.h"

#include "hittable.h"

bool Lambertian::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	auto scatterDirection = rec.normal + randomUnitVector();

	if(scatterDirection.isNearZero())
	{
		scatterDirection = rec.normal;
	}

	scattered = Ray(rec.p, scatterDirection);
	attenuation = m_albedo;
	return true;
}

bool Metal::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	const Vec3 reflected = reflect(unitVector(rIn.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + m_fuzz*randomUnitVector());
	attenuation = m_albedo;
	return dot(scattered.direction(), rec.normal) > 0;
}

bool Dialectric::scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0, 1.0, 1.0);
	double refractionRatio = rec.frontFace ? (1.0 / m_ir) : m_ir;

	Vec3 unitDirection = unitVector(rIn.direction());

	double cosTheta = std::min<double>(dot(-unitDirection, rec.normal), 1.0);
	double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0;
	Vec3 direction;


	if(cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble())
	{
		direction = reflect(unitDirection, rec.normal);
	}
	else
	{
		direction = refract(unitDirection, rec.normal, refractionRatio);
	}


	scattered = Ray(rec.p, direction);
	return true;
}


namespace 
{
	double reflectance(double cosine, double refIdx)
	{
		double r0 = (1 - refIdx) / (1 + refIdx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow(1 - cosine, 5);
	}
}
