//
// Created by Yoyotao on 2022/5/27.
//

#ifndef RAYTRACER_RANDOM_UTIL_H
#define RAYTRACER_RANDOM_UTIL_H

#include <random>
#include <ctime>

#include "vector3.h"



class RandomUtil {
public:
    template<typename T>
    static void Initial(T s) { e_.seed(s); }

    static float GetUniformFloat(float a, float b) {
        static std::uniform_real_distribution<float> u(0, 1);
        return u(e_) * (b - a) + a;
    }

    /**
     * 在半球上随机均匀采样
     * @return
     */
    static Vector3 SampleUniform() {
        // Marsaglia算法
        float x_1 = 0.f, x_2 = 0.f;
        do {
            x_1 = GetUniformFloat(-1, 1);
            x_2 = GetUniformFloat(-1, 1);
        } while (x_1 * x_1 + x_2 * x_2 >= 1);
        float x = 2 * x_1 * sqrtf(1 - x_1 * x_1 - x_2 * x_2);
        float y = 2 * x_2 * sqrtf(1 - x_1 * x_1 - x_2 * x_2);
        float z = 1 - 2 * (x_1 * x_1 + x_2 * x_2);
        Vector3 v{x, y, z}, n{0, 0, 1};
        if (v.Dot(n) < 0.f)
            return -v;
        else
            return v;
    }

    /**
     * 使用余弦权重的重要性采样
     * @return
     */
    static Vector3 SampleCosine() {
        float x_1 = GetUniformFloat(0.f, 1.f);
        float x_2 = GetUniformFloat(0.f, 1.f);
        float x = cosf(2.f * kFloatPi * x_2) * sqrtf(x_1);
        float y = sinf(2.f * kFloatPi * x_2) * sqrtf(x_1);
        float z = sqrtf(1 - x_1);
        return {x, y, z};
    }

private:
    static std::default_random_engine e_; // 声明
};


#endif //RAYTRACER_RANDOM_UTIL_H
