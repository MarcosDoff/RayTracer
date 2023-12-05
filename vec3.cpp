#include "vec3.h"

#include <complex.h>

#include "utils.h"

Vec3::Vec3() : e{0.0, 0.0, 0.0}
{
}

Vec3::Vec3(double x, double y, double z) : e{x, y, z}
{
}

double Vec3::x() const
{
	return e[0];
}

double Vec3::y() const
{
	return e[1];
}

double Vec3::z() const
{
	return e[2];
}

Vec3 Vec3::operator-() const
{
	return {-e[0], -e[1], -e[2]};
}

double Vec3::operator[](int i) const
{
	return e[i];
}

double& Vec3::operator[](int i)
{
	return e[i];
}

Vec3& Vec3::operator+=(const Vec3& v)
{
	e[0] += v.x();
	e[1] += v.y();
	e[2] += v.z();
	return *this;
}

Vec3& Vec3::operator*=(double t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

Vec3& Vec3::operator/=(double t)
{
	return *this *= 1 / t;
}

Vec3 Vec3::random(double min, double max)
{
	return {randomDouble(min, max), randomDouble(min, max), randomDouble(min, max)};
}

double Vec3::length() const
{
	return std::sqrt(lengthSquared());
}

double Vec3::lengthSquared() const
{
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

bool Vec3::isNearZero() const
{
	constexpr auto s = 1e-8;
	return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
	return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return {u.x() + v.x(), u.y() + v.y(), u.z() + v.z()};
}

Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return {u.x() - v.x(), u.y() - v.y(), u.z() - v.z()};
}

Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return {u.x() * v.x(), u.y() * v.y(), u.z() * v.z()};
}

Vec3 operator*(double t, const Vec3& v)
{
	return {t * v.x(), t * v.y(), t * v.z()};
}

Vec3 operator*(const Vec3& v, double t)
{
	return t * v;
}

Vec3 operator/(Vec3 v, double t)
{
	return (1 / t) * v;
}

double dot(const Vec3& u, const Vec3& v)
{
	return u.x() * v.x()
		+ u.y() * v.y()
		+ u.z() * v.z();
}

Vec3 cross(const Vec3& u, const Vec3& v)
{
	return {
		u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x()
	};
}

Vec3 unitVector(Vec3 v)
{
	return v / v.length();
}

Vec3 randomUnitVector()
{
	return unitVector(Vec3::random(-1, 1));
}

Vec3 randomOnHemisphere(const Vec3& normal)
{
	const Vec3 random = Vec3::random(-1, 1);
	return unitVector(dot(random, normal) * random);
}


Vec3 reflect(const Vec3& v, const Vec3& normal)
{
	return v - 2 * dot(v, normal) * normal;
}

Vec3 refract(const Vec3& v, const Vec3& normal, double etaiOverEtat)
{
	const double cosTheta = std::min<double>(dot(-v, normal), 1.0);
	const Vec3 rOutPerp = etaiOverEtat * (v + cosTheta * normal);
	const Vec3 rOutPara = -std::sqrt(fabs(1.0 - rOutPerp.lengthSquared())) * normal;
	return rOutPerp + rOutPara;
}
