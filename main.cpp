#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <random>

#include "ray.h"
#include "Geometry/plane.h"
#include "Material/lambert.h"
#include "Material/emissive.h"
#include "Utils/random_util.h"
#include "Utils/pdf.h"
#include "Texture/constant_texture.h"
#include "camera.h"
#include "world.h"

#pragma GCC optimize(3,"Ofast","inline") // 开启优化

const int kWidth = 600;
const int kHeight = 600;
const int kSamplesPerPixel = 100;
const int kDepth = 5;
const float kFieldOfView = 20.f; // kFieldOfView = Alpha / 2

void InitialScene(World &world);

int main() {
    clock_t start_time, end_time;
    RandomUtil::Initial(time(nullptr));

    start_time = clock();
    std::vector<std::vector<Vector3>> pixels_color(kHeight, std::vector<Vector3>(kWidth, Vector3()));

    Camera camera{{278.f, -800.f, 278.f},
                  {0.f, 1.f, 0.f},
                  {0.f, 0.f, 1.f}, kWidth, kHeight, kFieldOfView};

    // Initial Scene
    World world;
    InitialScene(world);

    // Get Pixel coordinates
    for (int pixel_idx = 0; pixel_idx < kWidth; ++pixel_idx) {
        for (int pixel_idy = 0; pixel_idy < kHeight; ++pixel_idy) {
            Vector3 pixel_color;
            for (int i = 0; i < kSamplesPerPixel; ++i) {
                Ray in_ray = camera.GetRay(pixel_idx, pixel_idy);
                pixel_color += world.CastRay(in_ray, kDepth);
            }
            pixel_color /= kSamplesPerPixel;
            pixels_color.at(pixel_idy).at(pixel_idx) = pixel_color;
        }
    }

    std::ofstream out_file("Image.ppm");
    out_file << "P3\n" << kWidth << " " << kHeight << " \n" << "255\n";
    for (int i = kHeight - 1; i >= 0; --i) {
        for (int j = 0; j < kWidth; ++j) {
            Vector3 color = pixels_color.at(i).at(j);
            int r_int = static_cast<int>(color.X() * 255.99f);
            int g_int = static_cast<int>(color.Y() * 255.99f);
            int b_int = static_cast<int>(color.Z() * 255.99f);
            out_file << r_int << " " << g_int << " " << b_int << "\n";
        }
    }
    out_file.close();

    end_time = clock();
    std::cout << "The run time is: " << (double) (end_time - start_time) / CLOCKS_PER_SEC << "s" << std::endl;
    return 0;
}

void InitialScene(World& world) {
    auto m_red = std::make_shared<Lambert>(std::make_shared<ConstantTexture>(Vector3{0.65f, 0.05f, 0.05f}));
    auto m_white = std::make_shared<Lambert>(std::make_shared<ConstantTexture>(Vector3{0.73f, 0.73f, 0.73f}));
    auto m_green = std::make_shared<Lambert>(std::make_shared<ConstantTexture>(Vector3{0.12f, 0.45f, 0.15f}));
    auto m_emissive = std::make_shared<Emissive>(std::make_shared<ConstantTexture>(Vector3{15.f, 15.f, 15.f}));

    world.Add(new Plane( // y-z x = 555
            {Vector3{555.f, 0.f, 555.f}, Vector3{555.f, 555.f, 555.f}, Vector3{555.f, 555.f, 0.f},
             Vector3{555.f, 0.f, 0.f}}, {-1.f, 0.f, 0.f}, m_green));
    world.Add(new Plane( // y-z x = 0
            {Vector3{0.f, 0.f, 555.f}, Vector3{0.f, 555.f, 555.f}, Vector3{0.f, 555.f, 0.f},
             Vector3{0.f, 0.f, 0.f}}, {1.f, 0.f, 0.f}, m_red));
    world.Add(new Plane( // light
            {Vector3{213.f, 227.f, 554.f}, Vector3{213.f, 332.f, 554.f}, Vector3{343.f, 332.f, 554.f},
             Vector3{343.f, 227.f, 554.f}}, {0.f, 0.f, -1.f}, m_emissive, false), HittableType::kLight);
    world.Add(new Plane( // x-z y = 555
            {Vector3{555.f, 555.f, 555.f}, Vector3{0.f, 555.f, 555.f}, Vector3{0.f, 555.f, 0.f},
             Vector3{555.f, 555.f, 0.f}}, {0.f, -1.f, 0.f}, m_white));
    world.Add(new Plane( // x-y z = 0
            {Vector3{0.f, 0.f, 0.f}, Vector3{0.f, 555.f, 0.f}, Vector3{555.f, 555.f, 0.f},
             Vector3{555.f, 0.f, 0.f}}, {0.f, 0.f, 1.f}, m_white));
    world.Add(new Plane( // x-y z = 555
            {Vector3{0.f, 0.f, 555.f}, Vector3{0.f, 555.f, 555.f}, Vector3{555.f, 555.f, 555.f},
             Vector3{555.f, 0.f, 555.f}}, {0.f, 0.f, -1.f}, m_white));

//    auto *box_1 = new Box(
//            {Vector3{5.f, 5.f, -6.f}, Vector3{-5.f, 5.f, -6.f}, Vector3{-5.f, 3.f, -8.f}, Vector3{5.f, 3.f, -8.f},
//             Vector3{5.f, 0.f, -6.f}, Vector3{-5.f, 0.f, -6.f}, Vector3{-5.f, -2.f, -8.f}, Vector3{5.f, -2.f, -8.f}},
//            m_lambert);
////    hittable_list_.push_back(box_1);

}