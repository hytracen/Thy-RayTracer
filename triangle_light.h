//
// Created by Yoyotao on 2022/5/23.
//

#ifndef RAYTRACER_TRIANGLE_LIGHT_H
#define RAYTRACER_TRIANGLE_LIGHT_H

#include <iostream>
#include <array>
#include "light.h"

class TriangleLight : public Light{
public:
    explicit TriangleLight(std::array<Vector3, 3> vertexes, std::shared_ptr<Material> mat) : vertexes_(vertexes) {
        mat_ = mat;
    };

    bool Hit(Ray in_ray, HitRec &hit_rec) override;

    Vector3 ColorAtPoint(Vector3 point) override;

    std::array<Vector3, 3> vertexes_; //顺时针
};


#endif //RAYTRACER_TRIANGLE_LIGHT_H
