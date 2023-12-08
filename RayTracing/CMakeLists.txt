# CMakeList.txt : CMake project for RayTracing, include source and define
# project specific logic here.
#

include_directories(../dependencies/GLFW/include/)
link_directories(../dependencies/GLFW/lib-vc2022/)


include_directories(../dependencies/GLEW/include/)
link_directories(../dependencies/GLEW/lib/)


add_executable (RayTracing "RayTracing.cpp"  "vec3.h" "vec3.cpp" "color.h" "color.cpp" "ray.h" "ray.cpp" "hittable.h" "sphere.h" "sphere.cpp" "hittablelist.h" "hittablelist.cpp" "utils.h" "camera.h" "camera.cpp" "material.h" "material.cpp")
set(CMAKE_CXX_STANDARD 17)
target_link_libraries(RayTracing glfw3)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracing PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
