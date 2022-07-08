//
// Created by Yoyotao on 2022/5/23.
//

#include "triangle.h"

bool Triangle::Hit(const Ray &in_ray, HitRec &hit_rec) {
    // Möller Trumbore Algorithm

    Vector3 E_1 = vertexes_.at(1) - vertexes_.at(0);
    Vector3 E_2 = vertexes_.at(2) - vertexes_.at(0);
    Vector3 S = in_ray.GetOrig() - vertexes_.at(0);
    Vector3 S_1 = in_ray.GetDir().Cross(E_2);
    Vector3 S_2 = S.Cross(E_1);

    float delta = S_1.Dot(E_1);
    float se_inv = 1.f / delta;
    float t = se_inv * S_2.Dot(E_2);
    float b_1 = se_inv * S_1.Dot(S);
    float b_2 = se_inv * S_2.Dot(in_ray.GetDir());
    if (t > 0.001f && t < FLT_MAX && (1 - b_1 - b_2) > 0.f && b_1 > 0.f && b_2 > 0.f) {
        hit_rec.ray_t = t;
        hit_rec.is_hit = true;
        hit_rec.is_front = in_ray.GetDir().Dot(normal_) < 0.f;
        hit_rec.hit_pos = in_ray.At(t);
        hit_rec.color = mat_->texture_->AlbedoAtTexel(0.f, 0.f, Vector3());
        hit_rec.normal = GetNormalAt(in_ray, {});
        hit_rec.hit_object = this;
        return true;
    } else {
        hit_rec.is_hit = false;
        return false;
    }
}

/**
 * 三角形面积公式 : sqrt(s(s-a)(s-b)(s-c)), s = (a+b+c)/2
 * @return 面积
 */
float Triangle::GetArea() {
    float a = GetDistanceBetween2Points(vertexes_.at(0), vertexes_.at(1));
    float b = GetDistanceBetween2Points(vertexes_.at(1), vertexes_.at(2));
    float c = GetDistanceBetween2Points(vertexes_.at(2), vertexes_.at(0));
    float s = (a + b + c) / 2;

    return sqrtf(s * (s - a) * (s - b) * (s - c));
}

// todo: 取消自动反转
Vector3 Triangle::GetNormalAt(const Ray &in_ray, const Vector3 &point) {
    if (hittable_attrib_.is_2sided_) { // 让法线方向总是against光线方向
        if (in_ray.GetDir().Dot(normal_) >= 0.f) {
            return -normal_;
        } else {
            return normal_;
        }
    } else {
        return normal_;
    }
}

std::vector<Triangle *> Triangle::GetTriList() {
    return triangles_;
}

void Triangle::RotateAround(Vector3 p, Vector3 dir, float angle) {
    float radian = angle / 180.f * (float)M_PI;
    // 旋转坐标
    for (auto &v : vertexes_) {
        v = v - p; // 平移至原点
        v = v * cosf(radian) + dir.Cross(v) * sinf(radian) + dir * dir.Dot(v) * (1 - cosf(radian)); // 绕轴旋转
        v = v + p;
    }
    // 旋转法线
    normal_ = normal_ * cosf(radian) + dir.Cross(normal_) * sinf(radian) + dir * dir.Dot(normal_) * (1 - cosf(radian)); // 绕轴旋转
    // 旋转重心
    barycenter_ = barycenter_ - p;
    barycenter_ = barycenter_ * cosf(radian) + dir.Cross(barycenter_) * sinf(radian) + dir * dir.Dot(barycenter_) * (1 - cosf(radian)); // 绕轴旋转
    barycenter_ = barycenter_ + p;
}

void Triangle::MoveBy(Vector3 dir, float dis) {
    Vector3 d = dir.Normalize() * dis;
    // 移动坐标
    for (auto &v : vertexes_) {
        v = v + d;
    }
    // 移动重心
    barycenter_ = barycenter_ + d;
}
