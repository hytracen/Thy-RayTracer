//
// Created by Yoyotao on 2022/5/30.
//

#ifndef RAYTRACER_PDF_H
#define RAYTRACER_PDF_H

#include "vector3.h"

class Pdf {
public:
    // 在半球上进行均匀采样
    static float GetUniHemiVal() { return 1 / (2 * M_PI); }

    // 对面积进行均匀采样
    static float GetUniAreaVal(float a) { return 1 / a; }
};


#endif //RAYTRACER_PDF_H
