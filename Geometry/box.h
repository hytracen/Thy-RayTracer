//
// Created by Yoyotao on 2022/5/30.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include "../hittable.h"
#include "plane.h"

class Box : public Hittable{
public:
    // 顶点数组的顺序为顺时针，自上而下
    Box(std::array<Vector3, 8> vertexes, std::shared_ptr<Material> material) : vertexes_(vertexes) {
        mat_ = (material);
    }

    bool Hit(Ray in_ray, HitRec &hit_rec) override;

    Vector3 GetNormalAtPoint(const Vector3 &point) override;

private:
    std::array<Vector3, 8> vertexes_; // 顺时针，自上而下初始化
};


#endif //RAYTRACER_BOX_H
