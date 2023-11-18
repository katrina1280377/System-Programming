// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu

#include <iostream>
#include "Vector.h"
#include <string>
using std::cout;
using std::cerr;
using std::endl;
static const float x1 = 1.1;
static const float y1 = 2.2;
static const float z1 = 3.3;
static const float x2 = 4.4;
static const float y2 = 5.5;
static const float z2 = 6.6;

// Verify the correct behaviour of the defined ctor/cctor
static void Verify(const Vector& v, const float x,
                   const float y, const float z);
// Add the vector called "add" to see if the v will be changed
static void Increment(Vector v);
// True if the address of v the same with p
static bool VerifyAddress(Vector v, void* p);

int main(int argc, char** argv) {
  // Constructor tests
  Vector v_1;
  Vector v_2(x1, y1, z1);
  Vector v_3(v_2);
  cout << "[Test] default constructor (v1)" << endl;
  Verify(v_1, 0, 0, 0);
  cout << endl << "[Test] 3 arguments (v2)" << endl;
  Verify(v_2, x1, y1, z1);
  cout << endl << "[Test] Copy constructor (v3)" << endl;
  Verify(v_3, x1, y1, z1);

  // Assignment tests
  cout << endl << "[Test] assignment operators (v1 = v3 = v4)" << endl;
  Vector v_4(x2, y2, z2);
  v_1 = v_3 = v_4;
  cout << "=== v1 verify ===" << endl;
  Verify(v_1, x2, y2, z2);
  cout << "=== v3 verify ===" << endl;
  Verify(v_3, x2, y2, z2);
  cout << "=== v4 verify ===" << endl;
  Verify(v_4, x2, y2, z2);


  cout << endl << "[Test] assignment operators (v1 = v2 += v3)" << endl;
  v_1 = v_2 += v_3;
  cout << "=== v1 verify ===" << endl;
  Verify(v_1, x1+x2, y1+y2, z1+z2);
  cout << "=== v2 verify ===" << endl;
  Verify(v_2, x1+x2, y1+y2, z1+z2);
  cout << "=== v3 verify ===" << endl;
  Verify(v_3, x2, y2, z2);

  cout << endl << "[Test] assignment operators (v1 = v2 -= v3)" << endl;
  v_1 = v_2 -= v_3;
  cout << "=== v1 verify ===" << endl;
  Verify(v_1, x1+x2-x2, y1+y2-y2, z1+z2-z2);
  cout << "=== v2 verify ===" << endl;
  Verify(v_1, x1+x2-x2, y1+y2-y2, z1+z2-z2);
  cout << "=== v3 verify ===" << endl;
  Verify(v_3, x2, y2, z2);

  cout << endl << "[Test] assignment operators (*)" << endl;
  float product = v_3*v_4;

  cout << "v2 * v3 = " << product << endl;
  if (product != x2 * x2 + y2 * y2 + z2 * z2) {
    cerr << "Test * assignment failed!" << endl;
    return EXIT_FAILURE;
  }

  cout << endl << "[Test] Increment function" << endl;
  Vector v(x1, y1, z1);
  Increment(v);

  if (v.get_x() == x1 && v.get_y() == y1 && v.get_z() == z1) {
    cout << "Vector: pass-by-value" << endl;
  } else {
    cout << "Vector: pass-by-reference" << endl;
  }

  cout << endl << "[Test] VerifyAddress function" << endl;
  if (VerifyAddress(v, &v)) {
    cout << "Ref: same address" << endl;
  } else {
    cout << "Ref: different address" << endl;
  }
  cout << endl << "Finish Test!!" << endl;
  return EXIT_SUCCESS;
}

static void Verify(const Vector& v, const float x,
                   const float y, const float z) {
  cout << "Vector: ";
  cout <<"("<< v.get_x()<<", "<< v.get_y()<<", "<<v.get_z()<< ")"<<endl;
  if (x != v.get_x() || y != v.get_y() || z != v.get_z()) {
    cerr << "Failed: the vector does not align with ";
    cerr << "(" << x << ", "<< y << ", " << z << ")" << endl;
    exit(EXIT_FAILURE);
  }
}

static void Increment(Vector v) {
  Vector add(1, 2, 3);
  v += add;
}

static bool VerifyAddress(Vector v, void* v_) {
  return &v == reinterpret_cast<Vector*>(v_);
}
