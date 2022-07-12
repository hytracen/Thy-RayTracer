//
// Created by Yoyotao on 2022/7/12.
//

#ifndef RAYTRACER_AREA_LIGHT_H
#define RAYTRACER_AREA_LIGHT_H

#include "light.h"
#include "../Utils/random_util.h"
#include "../Geometry/triangle.h"

class AreaLight : public Light {
public:
    AreaLight(Vector3 center, Vector3 len_vector, Vector3 wid_vec, Vector3 normal, std::shared_ptr<Material> mat, HittableAttrib hittable_attrib);

    Vector3 SamplePoint() const override;

    bool Hit(const Ray &in_ray, HitRec &hit_rec) override;

    Vector3 GetNormalAt(const Ray &in_ray, const Vector3 &point) override;

    std::vector<Triangle *> GetTriList() override;

    void RotateAround(Vector3 p, Vector3 dir, float angle) override;

    void MoveBy(Vector3 dir, float dis) override;

private:
    Vector3 l_vec_, w_vec_; // 长和宽的向量
    Vector3 center_; // 中心坐标
    Vector3 normal_;
};


#endif //RAYTRACER_AREA_LIGHT_H
