//
// Created by Yoyotao on 2022/6/2.
//

#ifndef RAYTRACER_CONSTANT_VALUE_H
#define RAYTRACER_CONSTANT_VALUE_H

const int kWidth = 600;
const int kHeight = 600;
const int kSamplesPerPixel = 100;
const int kDepth = 5;
const int kLeafTriNum = 2; // BVH数叶子节点所包含的最多的三角形的数量
const float kFieldOfView = 20.f; // kFieldOfView = Alpha / 2
const float kRR = 0.8f; // 俄罗斯轮盘赌
const float kEpsilon = 1e-6; // 浮点数误差
const float kFloatPi = 3.141592f;

#endif //RAYTRACER_CONSTANT_VALUE_H
