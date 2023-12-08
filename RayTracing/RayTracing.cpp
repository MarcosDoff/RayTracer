// RayTracing.cpp : Defines the entry point for the application.
//

#include "hittablelist.h"
#include "sphere.h"
#include "camera.h"
#include "utils.h"
#include "color.h"
#include "material.h"

#include <GLFW/glfw3.h>

int main()
{
	GLFWwindow* window;

	if(!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

	//world

	HittableList world;
	const auto materialGround = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(Point3(0, -6001, -1), 6000, materialGround));


	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; ++b)
		{
			const auto chooseMat = randomDouble();
			Point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

			if ((center - Point3(4.0, 2, 0)).length() > 0.9)
			{
				std::shared_ptr<Material> sphereMaterial;

				if (chooseMat < 0.8)
				{
					auto albedo = Color::random() * Color::random();
					sphereMaterial = std::make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else if (chooseMat < 0.95)
				{
					auto albedo = Color::random(0.5, 1);
					auto fuzz = randomDouble(0, 0.5);
					sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
				else
				{
					sphereMaterial = std::make_shared<Dialectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dialectric>(1.5);
	world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

	auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));


	const Camera camera;
	camera.render(world);


	std::clog << "\r Done!                                 \n";
}
