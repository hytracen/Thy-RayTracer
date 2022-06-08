//
// Created by Yoyotao on 2022/5/23.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include <iostream>
#include <array>
#include <algorithm>

#include "../hittable.h"
#include "../Material/material.h"
#include "../Utils/numeric.h"

class Triangle : public Hittable {
public:
    Triangle(std::array<Vector3, 3> vertexes, std::shared_ptr<Material> mat,
                      HittableAttrib hittable_attrib = HittableAttrib()) : vertexes_(vertexes) {
        normal_ = ((vertexes_.at(1) - vertexes_.at(0)).Cross(vertexes_.at(2)-vertexes_.at(0))).Normalize();
        barycenter_ = 1.f / 3.f * std::accumulate(vertexes_.begin(), vertexes_.end(), Vector3());
        mat_ = mat;
        hittable_attrib_ = hittable_attrib;
    };

    Triangle(std::array<Vector3, 3> vertexes, Vector3 normal, std::shared_ptr<Material> mat,
             HittableAttrib hittable_attrib = HittableAttrib()) : vertexes_(vertexes), normal_(normal) {
        barycenter_ = 1.f / 3.f * std::accumulate(vertexes_.begin(), vertexes_.end(), Vector3());
        mat_ = mat;
        hittable_attrib_ = hittable_attrib;
    }

    bool Hit(const Ray &in_ray, HitRec &hit_rec) override;

    Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point) override;

    std::vector<Triangle *> GetTriList() override;

    float GetArea();

public:
    std::array<Vector3, 3> vertexes_; // 逆时针的顶点集
    Vector3 barycenter_; // 重心
    Vector3 normal_; // 法线
};


#endif //RAYTRACER_TRIANGLE_H
