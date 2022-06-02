//
// Created by Yoyotao on 2022/5/30.
//

#ifndef RAYTRACER_PDF_H
#define RAYTRACER_PDF_H

#include "vector3.h"

class Pdf {
public:
    // 在半球上进行均匀采样的PDF
    static float GetUniHemiPdf() { return 1 / (2 * M_PI); }

    static float GetCosineHemiPdf(const Vector3 &out_dir, const Vector3 &n) {
        return CosThetaOf2Vec(out_dir, n) / kFloatPi;
    }

    // 对面积进行均匀采样的PDF
    static float GetUniAreaPdf(float a) { return 1 / a; }
};


#endif //RAYTRACER_PDF_H
