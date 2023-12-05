# CMakeList.txt : CMake project for RayTracing, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (RayTracing "RayTracing.cpp"  "vec3.h" "vec3.cpp" "color.h" "color.cpp" "ray.h" "ray.cpp" "hittable.h" "sphere.h" "sphere.cpp" "hittablelist.h" "hittablelist.cpp" "utils.h" "camera.h" "camera.cpp" "material.h" "material.cpp")
set(CMAKE_CXX_STANDARD 17)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracing PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
