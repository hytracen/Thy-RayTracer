#ifndef RAYTRACER_LAMBERT_H
#define RAYTRACER_LAMBERT_H

#include "material.h"
#include "../hit_rec.h"
#include "../Utils/random_util.h"

class Lambert : public Material{
public:
    explicit Lambert(std::shared_ptr<Texture> texture);
    explicit Lambert(const Vector3 &albedo);

    Vector3 BSDF(const Ray &in_ray, const Ray &out_ray, const Vector3 &n) override;

    Ray Scatter(const Ray &in_ray, const HitRec &hit_rec) override;
};


#endif //RAYTRACER_LAMBERT_H
