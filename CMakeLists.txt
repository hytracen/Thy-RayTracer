cmake_minimum_required(VERSION 3.22)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracer main.cpp ray.cpp ray.h Utils/vector3.cpp Utils/vector3.h hittable.cpp hittable.h Geometry/sphere.cpp Geometry/sphere.h Geometry/triangle.cpp Geometry/triangle.h Material/material.cpp Material/material.h Material/lambert.cpp Material/lambert.h hit_rec.h Material/emissive.cpp Material/emissive.h Utils/random_util.cpp Utils/random_util.h Texture/texture.cpp Texture/texture.h Texture/constant_texture.cpp Texture/constant_texture.h Utils/pdf.cpp Utils/pdf.h camera.cpp camera.h Geometry/plane.cpp Geometry/plane.h Geometry/box.cpp Geometry/box.h world.cpp world.h)
