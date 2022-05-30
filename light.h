//
// Created by Yoyotao on 2022/5/23.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "hittable.h"

class Light : public Hittable{
public:
    bool Hit(Ray in_ray, HitRec &hit_rec) override;

    Vector3 GetNormalAtPoint(Vector3 point) override;

    Vector3 ColorAtPoint(Vector3 point) override;
};


#endif //RAYTRACER_LIGHT_H
