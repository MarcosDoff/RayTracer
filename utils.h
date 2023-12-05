#pragma once

#include<cmath>
#include<limits>
#include <random>



//constants
const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;


//functions

inline double degreesToRadians(const double degrees)
{
	return degrees * pi / 180.0;
}

inline double radiansToDegrees(const double radians)
{
	return radians * 180.0 / pi;
}

inline double randomDouble()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double randomDouble(double min, double max)
{
	return min + (max - min) * randomDouble();
}