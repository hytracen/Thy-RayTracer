//
// Created by Yoyotao on 2022/5/26.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "../ray.h"
#include "../hit_rec.h"

class Material {
public:

    /// 根据入射光线和出射光线的方向求材质的BSDF值
    /// \param in_ray 入射光线
    /// \param out_ray 出射光线
    /// \return BSDF值
    virtual Vector3 BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) = 0;

    virtual bool IsScattered() const = 0;

};


#endif //RAYTRACER_MATERIAL_H
