//
// Created by Yoyotao on 2022/5/23.
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include <iostream>
#include <array>

#include "../hittable.h"
#include "../Material/material.h"

class Triangle : public Hittable {
public:
    explicit Triangle(std::array<Vector3, 3> vertexes, Vector3 normal, std::shared_ptr<Material> mat) : vertexes_(
            vertexes), normal_(normal.Normalize()) {
        mat_ = mat;
    };

    bool Hit(Ray in_ray, HitRec &hit_rec) override;

    Vector3 GetNormalAtPoint(const Vector3 &point) override;

    float GetArea();

public:
    std::array<Vector3, 3> vertexes_; // 顺时针的顶点集
    Vector3 normal_; // 法线
};


#endif //RAYTRACER_TRIANGLE_H