#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>

#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "triangle_light.h"
#include "Material/metal.h"
#include "Material/emissive.h"
#include "Utils/random_util.h"

const int kWidth = 640;
const int kHeight = 640;
const int kSamplesPerPixel = 20;
const int kDepth = 10;
const float kFieldOfView = 60.f; // Alpha/2

void InitialScene(std::vector<Hittable *> &hittable_list);

Vector3 CastRay(const Ray &in_ray, const std::vector<Hittable *> &hittable_list, int depth);

int main() {
    clock_t start_time, end_time;
    RandomUtil::Initial(time(nullptr));

    start_time = clock();
    std::vector<std::vector<Vector3>> pixels_color(kHeight, std::vector<Vector3>(kWidth, Vector3()));

    // Initial Scene
    std::vector<Hittable *> hittable_list;
    InitialScene(hittable_list);

    // Get Pixel coordinates
    for (int x = 0; x < kWidth; ++x) {
        for (int y = 0; y < kHeight; ++y) {
            float aspect_ratio = (float) kWidth / (float) kHeight;
            Vector3 pixel_color;
            for (int i = 0; i < kSamplesPerPixel; ++i) {
                float pixel_x = ((((float) x + RandomUtil::GetUniformFloat(0.f, 1.f)) / kWidth) * 2 - 1) * aspect_ratio *
                        (float) std::tan(kFieldOfView * M_PI / 180.f);
                float pixel_y = ((((float) y + RandomUtil::GetUniformFloat(0.f, 1.f)) / kHeight) * 2 - 1) *
                                (float) std::tan(kFieldOfView * M_PI / 180.f);
                float pixel_z = -1.f;
                Ray ray = Ray(Vector3(0.f, 0.f, 0.f), Vector3(pixel_x, pixel_y, pixel_z).Normalize());
                pixel_color += CastRay(ray, hittable_list, kDepth);
            }
            pixel_color /= kSamplesPerPixel;
            pixels_color.at(y).at(x) = pixel_color;
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

void InitialScene(std::vector<Hittable *> &hittable_list) {
    auto m_metal = std::make_shared<Metal>();
    auto m_emissive = std::make_shared<Emissive>();

    hittable_list.push_back(new Sphere({6.f, 0.f, -10.f}, 4.f, m_metal));
    hittable_list.push_back(new Sphere({-6.f, 0.f, -10.f}, 4.f, m_metal));
    // Initial Light
    auto *triangle_light_1 = new TriangleLight(
            std::array<Vector3, 3>{Vector3{5.f, 6.f, -5.f}, Vector3{-5.f, 6.f, -5.f}, Vector3{0.f, 6.f, -10.f}},
            m_emissive);
    hittable_list.push_back(triangle_light_1);

    auto *triangle_light_2 = new TriangleLight(
            std::array<Vector3, 3>{Vector3{5.f, -6.f, -5.f}, Vector3{-5.f, -6.f, -5.f}, Vector3{0.f, -6.f, -10.f}},
            m_emissive);
    hittable_list.push_back(triangle_light_2);
}

Vector3 CastRay(const Ray &in_ray, const std::vector<Hittable *> &hittable_list, int depth) {
    if (depth <= 0) return {}; // 达到最大递归深度，递归结束
//    Vector3 color;
    for (auto *hittable: hittable_list) {
        HitRec hit_rec;
        if (hittable->Hit(in_ray, hit_rec)) { // 光线击中物体
            if (hittable->mat_->IsScattered()) { // 光线发生散射
                Ray scattered_ray;
                scattered_ray.SetOrig(hit_rec.hit_pos);
                scattered_ray.SetDir(LocalToWorld(RandomUtil::GetRandomPointOnHemisphere(), hit_rec.normal));
                return  hittable->mat_->BSDF(in_ray, scattered_ray, hit_rec.normal) *
                        CastRay(scattered_ray, hittable_list, depth - 1);
            } else { // 光线不发生反射，递归结束
                return hit_rec.color;
            }
            break; // 光线只能击中一个物体
        }
    }
    return {};
}