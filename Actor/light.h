//
// Created by Yoyotao on 2022/7/12.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "../hittable.h"

class Light : public Hittable {
public:
    virtual Vector3 SamplePoint() const = 0;
};


#endif //RAYTRACER_LIGHT_H
