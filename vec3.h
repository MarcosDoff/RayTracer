#pragma once

#include <cmath>
#include <iostream>

class Vec3
{
public:
	Vec3();
	Vec3(double x, double y, double z);
	~Vec3() = default;

	double x() const;
	double y() const;
	double z() const;

	Vec3 operator-() const;
	double operator[](int i) const;
	double& operator[](int i);
	Vec3& operator+=(const Vec3& v);
	Vec3& operator*=(double t);
	Vec3& operator/=(double t);

	static Vec3 random(double min = 0.0, double max = 1.0);
	

	double length() const;
	double lengthSquared() const;

	bool isNearZero() const;


private:

	double e[3];
};

//alias
using Point3 = Vec3;

//aux functions

std::ostream& operator<<(std::ostream& out, const Vec3& v);

Vec3 operator+(const Vec3& u, const Vec3& v);

Vec3 operator-(const Vec3& u, const Vec3& v);

Vec3 operator*(const Vec3& u, const Vec3& v);

Vec3 operator*(double t, const Vec3& v);

Vec3 operator*(const Vec3& v, double t);

Vec3 operator/(Vec3 v, double t);

double dot(const Vec3& u, const Vec3& v);

Vec3 cross(const Vec3& u, const Vec3& v);

Vec3 unitVector(Vec3 v);

Vec3 randomVectorInUnitSphere();

Vec3 randomUnitVector();

Vec3 randomOnHemisphere(const Vec3& normal);

Vec3 reflect(const Vec3& v, const Vec3& normal);

Vec3 refract(const Vec3& v, const Vec3& normal, double etaiOverEtat);

