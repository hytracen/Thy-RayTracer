//
// Created by Yoyotao on 2022/5/5.
//

#include "hittable.h"

Vector3 Hittable::GetNormalAt(const Ray &in_ray, const Vector3 &point) {
    return {};
}

std::vector<Triangle *> Hittable::GetTriList() {
    return triangles_;
}

void Hittable::RotateAround(Vector3 p, Vector3 dir, float angle) {

}

void Hittable::MoveBy(Vector3 dir, float dis) {

}
