//
// Created by Yoyotao on 2022/5/4.
//

#include "vector3.h"

Vector3 Vector3::Normalize() const {
    return {x_ / Length(), y_ / Length(), z_ / Length()};
}

float Vector3::Length() const {
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

Vector3 Vector3::Cross(Vector3 v) const {
    return Vector3{this->Y() * v.Z() - this->Z() * v.Y(), this->Z() * v.X() - this->X() * v.Z(),
                   this->X() * v.Y() - this->Y() * v.X()};
}

float Vector3::Dot(Vector3 v) const {
    return this->X() * v.X() + this->Y() * v.Y() + this->Z() * v.Z();
}

Vector3 operator+(Vector3 v1, Vector3 v2) {
    return {v1.X() + v2.X(), v1.Y() + v2.Y(), v1.Z() + v2.Z()};
}

Vector3 operator*(float t, Vector3 v) {
    return {t * v.X(), t * v.Y(), t * v.Z()};
}

Vector3 operator/(Vector3 v1, float t) {
    return (1 / t) * v1;
}

Vector3 operator-(Vector3 v1, Vector3 v2) {
    return {v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z()};
}

Vector3 operator-(Vector3 v) {
    return {-v.X(), -v.Y(), -v.Z()};
}

std::ostream & operator<<(std::ostream &os, const Vector3 &v) {
    os << "{ " << v.X() << ", " << v.Y() << ", " << v.Z() << "}" << std::endl;
    return os;
}

float GetDistanceBetween2Points(Vector3 v1, Vector3 v2) {
    return sqrtf(powf(v1.X() - v2.X(), 2) + powf(v1.Y() - v2.Y(), 2) + powf(v1.Z() - v2.Z(), 2));
}

float CosThetaOf2Vec(Vector3 v1, Vector3 v2) {
    return v1.Dot(v2) / (v1.Length() * v2.Length());
}

Vector3 LocalToWorld(Vector3 v_loc, Vector3 w) {
    Vector3 a;
    if (GetDistanceBetween2Points(w, Vector3(1, 0, 0)) <= 0.1f) {
        a = {0, 1, 0};
    } else {
        a = {1, 0, 0};
    }
    Vector3 u = w.Cross(a).Normalize(); // w和a的夹角并非90度，因此叉乘结果的模不为1，需要进行归一化
    Vector3 v = w.Cross(u);

    return v_loc.X() * u + v_loc.Y() * v + v_loc.Z() * w;
}