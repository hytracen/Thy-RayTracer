cmake_minimum_required(VERSION 3.22)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracer main.cpp ray.cpp ray.h Utils/vector3.cpp Utils/vector3.h hittable.cpp hittable.h sphere.cpp sphere.h light.cpp light.h triangle_light.cpp triangle_light.h Material/material.cpp Material/material.h Material/metal.cpp Material/metal.h hit_rec.h Material/emissive.cpp Material/emissive.h Utils/random_util.cpp Utils/random_util.h Texture/texture.cpp Texture/texture.h)
