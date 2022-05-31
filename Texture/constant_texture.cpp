//
// Created by Yoyotao on 2022/5/30.
//

#include "constant_texture.h"

Vector3 ConstantTexture::AlbedoAtTexel(float u, float v, const Vector3 &n) {
    return const_color_;
}
