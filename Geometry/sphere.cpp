//
// Created by Yoyotao on 2022/5/5.
//

#include "sphere.h"

/// \brief 球体与光线求交
/// \param in_ray 光线
/// \param hit_rec 描述相交结果的结构体
/// \return 是否相交
bool Sphere::Hit(const Ray &in_ray, HitRec &hit_rec) {
    float c_x = center_.GetX(), c_y = center_.GetY(), c_z = center_.GetZ(); // sphere的center坐标
    float o_x = in_ray.GetOrig().GetX(), o_y = in_ray.GetOrig().GetY(), o_z = in_ray.GetOrig().GetZ(); // ray的起点坐标
    float d_x = in_ray.GetDir().GetX(), d_y = in_ray.GetDir().GetY(), d_z = in_ray.GetDir().GetZ(); // ray的方向
    float a = powf(d_x, 2) + powf(d_y, 2) + powf(d_z, 2);
    float b = 2 * (d_x * (o_x - c_x) + d_y * (o_y - c_y) + d_z * (o_z - c_z));
    float c = powf((o_x - c_x), 2) + powf((o_y - c_y), 2) + powf((o_z - c_z), 2) - powf(radius_, 2);
    float delta = b * b - 4 * a * c;
    if (delta < 0.f) { // 如果Δ小于0，则没有交点
        hit_rec.is_hit = false;
        return false;
    }
    float t_1 = (-b - sqrtf(delta)) / (2 * a);
    float t_2 = (-b + sqrtf(delta)) / (2 * a);
    float t = t_1;

    const float t_min = 0.001f;
    const float t_max = FLT_MAX;

    // 取可接受范围(t_min, t_max)内的最小的t值
    if (t < t_min || t > t_max) {
        t = t_2;
        if (t < t_min || t > t_max) {
            hit_rec.is_hit = false;
            return false;
        }
    }

    hit_rec.ray_t = t;
    hit_rec.is_hit = true;
    hit_rec.is_front = in_ray.GetDir().Dot((in_ray.At(t) - center_).Normalize()) < 0.f;
    hit_rec.hit_pos = in_ray.At(t);
    hit_rec.color = mat_->texture_->AlbedoAtTexel(0.f, 0.f, Vector3());
    hit_rec.normal = GetNormalAt(in_ray, hit_rec.hit_pos);
    hit_rec.hit_object = this;
    return true;
}

Vector3 Sphere::GetNormalAt(const Ray &in_ray, const Vector3 &point) {
    Vector3 n = (point - center_).Normalize();
    if (hittable_attrib_.is_2sided_) { // 让法线方向总是against光线方向
        if (in_ray.GetDir().Dot(n) >= 0.f) {
            return -n;
        } else {
            return n;
        }
    } else {
        return n;
    }
}

std::vector<Triangle *> Sphere::GetTriList() {
    return Hittable::GetTriList();
}