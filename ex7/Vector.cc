// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu
#include <iostream>
#include "Vector.h"
using std::ostream;
namespace vector333 {

// default constructor (0,0,0)
Vector::Vector() {
    initial(0.0, 0.0, 0.0);
}

// constructor (x, y, z)
Vector::Vector(const float x, const float y, const float z) {
    initial(x, y, z);
}

// copy constructor
Vector::Vector(const Vector& v) {
    initial(v.arr_[0], v.arr_[1], v.arr_[2]);
}

// initialization function
void Vector::initial(const float x, const float y, const float z) {
  arr_ = new float[3];
  arr_[0] = x;
  arr_[1] = y;
  arr_[2] = z;
}

// destructor
Vector::~Vector() {
    delete [] arr_;
}

// assignment
Vector& Vector::operator=(const Vector& v) {
    if (this != &v) {
        arr_[0] = v.arr_[0];
        arr_[1] = v.arr_[1];
        arr_[2] = v.arr_[2];
    }
    return *this;
}

// updating assignments
Vector& Vector::operator+=(const Vector& v) {
    arr_[0] += v.arr_[0];
    arr_[1] += v.arr_[1];
    arr_[2] += v.arr_[2];
    return *this;
}

Vector& Vector::operator-=(const Vector& v) {
    arr_[0] -= v.arr_[0];
    arr_[1] -= v.arr_[1];
    arr_[2] -= v.arr_[2];
    return *this;
}

// Friend functions
// operator * should compute the inner product
float operator*(const Vector& a, const Vector& b) {
    return a.arr_[0]*b.arr_[0] + a.arr_[1]*b.arr_[1] + a.arr_[2]*b.arr_[2];
}
// operator * should also be overloaded
Vector operator*(const float k, const Vector& v) {
  return Vector(v.arr_[0] * k, v.arr_[1] * k, v.arr_[2] * k);
}
Vector operator*(const Vector& v, const float k) {
  return Vector(v.arr_[0] * k, v.arr_[1] * k, v.arr_[2] * k);
}

// Stream output
ostream& operator<<(ostream& out, const Vector& v) {
  out << "(" << v.arr_[0] << "," << v.arr_[1] << "," << v.arr_[2] << ")";
  return out;
}

// add funcition
Vector operator+(const Vector& a, const Vector& b) {
  Vector tmp = a;
  tmp += b;
  return tmp;
}

// sub funcition
Vector operator-(const Vector& a, const Vector& b) {
  Vector tmp = a;
  tmp -= b;
  return tmp;
}

}  // namespace vector333
