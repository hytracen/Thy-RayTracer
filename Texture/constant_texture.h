//
// Created by Yoyotao on 2022/5/30.
//

#ifndef RAYTRACER_CONSTANT_TEXTURE_H
#define RAYTRACER_CONSTANT_TEXTURE_H

#include "texture.h"

class ConstantTexture : public Texture {
public:
    explicit ConstantTexture(const Vector3 &const_color) : const_color_(const_color) {}
    Vector3 ColorAtTexel(float u, float v, const Vector3 &n) override;

private:
    Vector3 const_color_;
};


#endif //RAYTRACER_CONSTANT_TEXTURE_H
