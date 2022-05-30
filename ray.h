//
// Created by Yoyotao on 2022/5/4.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Utils/vector3.h"

class Ray {
public:
    Ray() : o_(Vector3()), d_(Vector3()), t_(0.f){}
    Ray(Vector3 orig, Vector3 dir) : o_(orig), d_(dir), t_(1.f){}
    Vector3 GetOrig() const {return o_;}
    Vector3 GetDir() const {return d_;}
    void SetOrig(Vector3 orig) { o_ = orig; }
    void SetDir(Vector3 dir) { d_ = dir; }
    Vector3 At(float t) const {return o_ + t * d_;}
private:
    Vector3 o_, d_;
    float t_;

};


#endif //RAYTRACER_RAY_H
