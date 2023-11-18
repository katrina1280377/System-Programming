// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu

#ifndef VECTOR_H_
#define VECTOR_H_
class Vector {
 public:
    // Default ctor
    Vector() : x_(0.0), y_(0.0), z_(0.0) { }
    // Three parameters
    Vector(const float x, const float y, const float z): x_(x), y_(y), z_(z) { }
    // cctor
    Vector(const Vector& v): x_(v.x_), y_(v.y_), z_(v.z_) { }
    // dtor
    ~Vector() { }
    // Assignment on vectors
    Vector& operator=(const Vector& v);
    // Getting x, y, z directions
    float get_x() const { return x_; }
    float get_y() const { return y_; }
    float get_z() const { return z_; }
    // Updating assignment on vectors
    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    // Compute inner product
    float operator*(const Vector& v) const;
 private:
    float x_, y_, z_;
};  // Class vector

#endif  // VECTOR_H_
