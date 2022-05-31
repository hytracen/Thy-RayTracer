#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>

#include "ray.h"
#include "hittable.h"
#include "Geometry/sphere.h"
#include "Geometry/plane.h"
#include "Geometry/box.h"
#include "Material/lambert.h"
#include "Material/emissive.h"
#include "Utils/random_util.h"
#include "Utils/pdf.h"
#include "Texture/constant_texture.h"
#include "camera.h"
#include "world.h"

//#pragma GCC optimize(2) // 开启优化

const int kWidth = 600;
const int kHeight = 600;
const int kSamplesPerPixel = 50;
const int kDepth = 5;
const float kFieldOfView = 20.f; // kFieldOfView = Alpha / 2
//const float kRR = 0.6f; // 俄罗斯轮盘赌
//const Vector3 kLightNormal{0.f, 0.f, -1.f};

void InitialScene(World &world);

//Vector3 CastRay(const Ray &in_ray, const std::vector<Hittable *> &hittable_list, int depth);

int main() {
    clock_t start_time, end_time;
    RandomUtil::Initial(time(nullptr));

    start_time = clock();
    std::vector<std::vector<Vector3>> pixels_color(kHeight, std::vector<Vector3>(kWidth, Vector3()));

    // todo:整理camera类
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

//    auto m_lambert = std::make_shared<Lambert>(std::make_shared<ConstantTexture>(Vector3{0.1f, 0.1f, 0.1f}));
//    auto m_emissive = std::make_shared<Emissive>(std::make_shared<ConstantTexture>(Vector3{20.f, 20.f, 20.f}));

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

////    hittable_list_.push_back(new Sphere({5.f, 0.f, -10.f}, 3.f, m_lambert));
////    hittable_list_.push_back(new Sphere({-5.f, 0.f, -10.f}, 3.f, m_lambert));
//    // Initial Light
//    auto *triangle_1 = new Triangle(
//            {Vector3{5.f, 6.f, -5.f}, Vector3{-5.f, 6.f, -5.f}, Vector3{0.f, 6.f, -10.f}},
//            {0.f, -1.f, 0.f},
//            m_emissive);
////    hittable_list_.push_back(triangle_1);
//
//    auto *triangle_light_2 = new Triangle(
//            {Vector3{5.f, -6.f, -5.f}, Vector3{-5.f, -6.f, -5.f}, Vector3{0.f, -6.f, -10.f}},
//            {0.f, 1.f, 0.f},
//            m_emissive);
////    hittable_list_.push_back(triangle_light_2);
//
//    auto *plane_1 = new Plane({Vector3{5.f, -3.f, -5.f}, Vector3{-5.f, -3.f, -5.f}, Vector3{-5.f, -3.f, -10.f},
//                               Vector3{5.f, -3.f, -10.f}},
//                              {0.f, 1.f, 0.f},
//                              m_lambert);
////    hittable_list_.push_back(plane_1);
//    auto *box_1 = new Box(
//            {Vector3{5.f, 5.f, -6.f}, Vector3{-5.f, 5.f, -6.f}, Vector3{-5.f, 3.f, -8.f}, Vector3{5.f, 3.f, -8.f},
//             Vector3{5.f, 0.f, -6.f}, Vector3{-5.f, 0.f, -6.f}, Vector3{-5.f, -2.f, -8.f}, Vector3{5.f, -2.f, -8.f}},
//            m_lambert);
////    hittable_list_.push_back(box_1);
//
//    auto *light_1 = new Plane({Vector3{5.f, -6.f, -5.f}, Vector3{-5.f, -6.f, -5.f}, Vector3{-5.f, -6.f, -10.f},
//                               Vector3{5.f, -6.f, -10.f}},
//                              {0.f, 1.f, 0.f},
//                              m_emissive);
////    hittable_list_.push_back(light_1);
}

//Vector3 CastRay(const Ray &in_ray, const std::vector<Hittable *> &hittable_list, int depth) {
//    if (depth <= 0) return {}; // 达到最大递归深度，递归结束
//
//    for (auto *hittable: hittable_list) {
//        HitRec hit_rec;
//        if (hittable->Hit(in_ray, hit_rec)) { // 光线击中物体
//            if ((!hittable->is_2sided_) && in_ray.GetDir().Dot(hit_rec.normal) > 0.f) // 物体为单面且光线击中物体背面
//                return {};
//            if (!hittable->mat_->IsScattered()) // 击中光源时，直接返回光源的颜色
//                return hit_rec.color;
//
//            // 在光源上随机取点
//            float x = RandomUtil::GetUniformFloat(213.f, 343.f);
//            float y = RandomUtil::GetUniformFloat(227.f, 332.f);
//            float z = 554.f;
//            float dis = GetDistanceBetween2Points({x, y, z}, hit_rec.hit_pos);
//            Ray ray_light{hit_rec.hit_pos, (Vector3{x, y, z} - hit_rec.hit_pos).Normalize()};
//            Vector3 r_dir;
//            if (ray_light.GetDir().Dot(kLightNormal) < 0.f) {
//                r_dir = hittable->mat_->BSDF(in_ray, ray_light, hit_rec.normal) * Vector3{15.f, 15.f, 15.f}
//                        * ray_light.GetDir().Dot(hit_rec.normal) * (-ray_light.GetDir()).Dot(kLightNormal)
//                        / powf(dis, 2) / Pdf::GetUniAreaVal(13650.f);
//            }
//
//            Ray scattered_ray;
//            scattered_ray.SetOrig(hit_rec.hit_pos);
//            scattered_ray.SetDir(LocalToWorld(RandomUtil::GetRandomPointOnHemisphere(), hit_rec.normal));
//            Vector3 r_indir = (scattered_ray.GetDir()).Dot(hit_rec.normal) *
//                              hittable->mat_->BSDF(in_ray, scattered_ray, hit_rec.normal) *
//                              CastRay(scattered_ray, hittable_list, depth - 1) / Pdf::GetUniHemiVal();
//
//            return r_dir + r_indir;
//        }
//    }
//    return {};
//}