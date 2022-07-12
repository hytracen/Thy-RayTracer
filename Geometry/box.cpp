//
// Created by Yoyotao on 2022/5/30.
//

#include "box.h"

Box::~Box() {
    for (auto & plane : planes_) {
        delete plane;
    }
}

bool Box::Hit(const Ray &in_ray, HitRec &hit_rec) {
    float t = std::numeric_limits<float>::max();
    bool is_hit = false;
    HitRec temp_hit_rec;
    for (auto p: planes_) {
        if (p->Hit(in_ray, temp_hit_rec)) {
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

Vector3 Box::GetNormalAt(const Ray &in_ray, const Vector3 &point) {
    return {};
}

std::vector<Triangle *> Box::GetTriList() {
    return triangles_;
}

void Box::RotateAround(Vector3 p, Vector3 dir, float angle) {
    for (auto tri : triangles_) {
        tri->RotateAround(p,dir,angle);
    }
}

void Box::MoveBy(Vector3 dir, float dis) {
    Hittable::MoveBy(dir, dis);
}
