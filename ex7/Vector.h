// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu

#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>

namespace vector333 {
class Vector {
 public:
    // default constructor (0,0,0)
    Vector();

    // constructor (x, y, z)
    Vector(const float x, const float y, const float z);

    // copy constructor
    Vector(const Vector& v);

    // destructor
    ~Vector();

    // assignment
    Vector& operator=(const Vector &v);

    // updating assignments
    Vector& operator+=(const Vector &v);
    Vector& operator-=(const Vector &v);

    // operator * should also be overloaded
    friend Vector operator*(float k, const Vector& v);
    friend Vector operator*(const Vector& v, float k);

    // operator * should compute the inner product
    friend float operator*(const Vector& a, const Vector& b);

    // Stream output
    friend std::ostream& operator<<(std::ostream& out, const Vector& v);

 private:
    float *arr_;
    void initial(const float x, const float y, const float z);
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);

}  // namespace vector333
#endif  // VECTOR_H_
