//
// Created by Yoyotao on 2022/7/12.
//

#include "area_light.h"

AreaLight::AreaLight(Vector3 center, Vector3 len_vector, Vector3 wid_vec, Vector3 normal, std::shared_ptr<Material> mat,
                     HittableAttrib hittable_attrib = HittableAttrib()) : center_(center),
                                                       l_vec_(len_vector),
                                                       w_vec_(wid_vec),
                                                       normal_(normal) {
    mat_ = mat;
    hittable_attrib_ = hittable_attrib;
    Vector3 p_1 = center - 0.5 * l_vec_ - 0.5 * w_vec_;
    Vector3 p_2 = center - 0.5 * l_vec_ + 0.5 * w_vec_;
    Vector3 p_3 = center + 0.5 * l_vec_ - 0.5 * w_vec_;
    Vector3 p_4 = center + 0.5 * l_vec_ + 0.5 * w_vec_;
    triangles_.push_back(new Triangle({p_1, p_2, p_4},normal_, mat_, hittable_attrib_));
    triangles_.push_back(new Triangle({p_1, p_3, p_4},normal_, mat_, hittable_attrib_));
};

Vector3 AreaLight::SamplePoint() const {
    float r_1 = RandomUtil::GetUniformFloat(-0.5, 0.5);
    float r_2 = RandomUtil::GetUniformFloat(-0.5, 0.5);
    return center_ + r_1 * l_vec_ + r_2 * w_vec_;
}

Vector3 AreaLight::GetNormalAt(const Ray &in_ray, const Vector3 &point) {
    return normal_;
}

std::vector<Triangle *> AreaLight::GetTriList() {
    return Hittable::GetTriList();
}

void AreaLight::RotateAround(Vector3 p, Vector3 dir, float angle) {
    for (auto tri : triangles_) {
        tri->RotateAround(p,dir,angle);
    }
}

void AreaLight::MoveBy(Vector3 dir, float dis) {
    for (auto tri : triangles_) {
        tri->MoveBy(dir, dis);
    }
}

bool AreaLight::Hit(const Ray &in_ray, HitRec &hit_rec) {
    float t = std::numeric_limits<float>::max();
    bool is_hit = false;
    HitRec temp_hit_rec;
    for (auto tri: triangles_) {
        if (tri->Hit(in_ray, temp_hit_rec)) {
            is_hit = true;
            if (temp_hit_rec.ray_t < t) {
                hit_rec = temp_hit_rec;
                hit_rec.hit_object = this;
                t = hit_rec.ray_t;
            }
        }
    }
    if (t < 0.01f) return false;
    return is_hit;
}
