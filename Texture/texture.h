//
// Created by Yoyotao on 2022/5/30.
//

#ifndef RAYTRACER_TEXTURE_H
#define RAYTRACER_TEXTURE_H

#include "../Utils/vector3.h"

class Texture {
    virtual Vector3 ColorAtTexel(float u, float v, const Vector3& n) = 0;
};


#endif //RAYTRACER_TEXTURE_H
