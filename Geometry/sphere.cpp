//
// Created by Yoyotao on 2022/5/5.
//

#include "sphere.h"

/// \brief 球体与光线求交
/// \param in_ray 光线
/// \param hit_rec 描述相交结果的结构体
/// \return 是否相交
bool Sphere::Hit(const Ray &in_ray, HitRec &hit_rec) {
    if (fabsf(GetDistanceBetween2Points(in_ray.GetOrig(), center_) - radius_) <= 0.1f) {
        hit_rec.is_hit = false;
        return false;
    }
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
    float t_1 = (-b + sqrtf(delta)) / (2 * a);
    float t_2 = (-b - sqrtf(delta)) / (2 * a);
    float t = 0.f;

    // 光线与球有两个交点时存在三种情况
    // 两个t均为正，说明交点在光线行进的方向
    if (t_1 > 0.f && t_2 > 0.f) {
        t = fminf(t_1, t_2);
    } else if (t_1 <= 0.f && t_2 <= 0.f) { // 两个t均为负，说明交点在光线行进的负向，此时认为没有交点
        hit_rec.is_hit = false;
        return false;
    } else { // 两个t一正一负，说明光线的起点在球内部，此时认为与球有一个交点，即t为正值的交点
        t = fmaxf(t_1, t_2);
    }

    hit_rec.is_hit = true;
    hit_rec.hit_pos = in_ray.At(t);
    hit_rec.color = mat_->texture_->AlbedoAtTexel(0.f, 0.f, Vector3());
    hit_rec.normal = GetNormalAt(in_ray, hit_rec.hit_pos);
    hit_rec.hit_object = this;
    return true;
}

Vector3 Sphere::GetNormalAt(const Ray &in_ray, const Vector3 &point) {
    return (point - center_).Normalize();
}
