//
// Created by Yoyotao on 2022/6/5.
//

#include "aabb.h"

bool Aabb::Hit(const Ray &in_ray, HitRec &hit_rec) {
    Vector3 dir_inv = in_ray.GetDir().Inv();
    float tx_min = (p_min_.GetX() - in_ray.GetOrig().GetX()) * dir_inv.GetX();
    float tx_max = (p_max_.GetX() - in_ray.GetOrig().GetX()) * dir_inv.GetX();
    float ty_min = (p_min_.GetY() - in_ray.GetOrig().GetY()) * dir_inv.GetY();
    float ty_max = (p_max_.GetY() - in_ray.GetOrig().GetY()) * dir_inv.GetY();
    float tz_min = (p_min_.GetZ() - in_ray.GetOrig().GetZ()) * dir_inv.GetZ();
    float tz_max = (p_max_.GetZ() - in_ray.GetOrig().GetZ()) * dir_inv.GetZ();

    if (in_ray.GetDir().GetX() < 0.f)
        std::swap(tx_min, tx_max);
    if (in_ray.GetDir().GetY() < 0.f)
        std::swap(ty_min, ty_max);
    if (in_ray.GetDir().GetZ() < 0.f)
        std::swap(tz_min, tz_max);

    float t_enter = std::max(tx_min, std::max(ty_min, tz_min));
    float t_exit = std::min(tx_max, std::min(ty_max, tz_max));

    if (t_exit >= t_enter && t_exit >= 0.f) {
        hit_rec.hit_object = this;
        hit_rec.hit_pos = in_ray.At(t_enter);
        hit_rec.is_hit = true;
        hit_rec.ray_t = t_enter;
        return true;
    }
    else
        return false;
}
