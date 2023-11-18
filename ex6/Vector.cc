// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu
#include <iostream>
#include "Vector.h"

Vector& Vector::operator=(const Vector& v) {
    if (this != &v) {
        x_ = v.x_;
        y_ = v.y_;
        z_ = v.z_;
    }
    return *this;
}

Vector& Vector::operator+=(const Vector& v) {
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;
    return *this;
}

Vector& Vector::operator-=(const Vector& v) {
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;
    return *this;
}

float Vector::operator*(const Vector& v) const {
    return x_*v.x_ + y_*v.y_ + z_*v.z_;
}
