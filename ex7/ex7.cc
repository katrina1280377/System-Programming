// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu

#include <iostream>
#include <cstdlib>
#include "Vector.h"
using std::cout;
using std::endl;
using vector333::Vector;
static const float x1 = 1.1;
static const float y1 = 2.2;
static const float z1 = 3.3;
static const float x2 = 4.4;
static const float y2 = 5.5;
static const float z2 = 6.6;

int main(int argc, char** argv) {
  // Constructor tests
  Vector v_1;
  Vector v_2(x1, y1, z1);
  Vector v_3(v_2);
  cout << "[Test] default constructor v1:(0, 0, 0): " << v_1 << endl;
  cout << "[Test] 3 arguments v2:(1.1, 2.2, 3.3): " << v_2 << endl;
  cout << "[Test] Copy constructor v3:(1.1, 2.2 ,3.3): " << v_3 << endl;

  // Assignment tests
  Vector v_4(x2, y2, z2);
  v_1 = v_3 = v_4;
  cout << "[Test] Vector assignment v4:(4.4, 5.5, 6.6): ";
  cout << "(v1) " << v_1 << " = (v3) " << v_3 << " = (v4) "<< v_4 << endl;

  // Updating assignment test
  v_1 = v_2 += v_3;
  cout << "[Test] Updating assignment v1 = v2 += v3 (5.5, 7.7, 9.9): ";
  cout << "(v1) " << v_1 << " = (v2) " << v_2 << endl;
  v_1 = v_2 -= v_3;
  cout << "[Test] Updating assignment v1 = v2 -= v3 (1.1, 2.2, 3.3): ";
  cout << "(v1) " << v_1 << " = (v2) " << v_2  << endl;

  // Add/Sub function
  cout << "[Test] Add function: " << v_1 << " + " << v_2 << " = ";
  cout << v_1+v_2 << endl;
  cout << "[Test] Sun function: " << v_1 << " - " << v_2 << " = ";
  cout << v_1-v_2 << endl;

  // dot product
  cout << "[Test] Dot product: (a,b,c) * (x,y,z) = ";
  cout << v_1 << " * " << v_2 << " = " << v_1*v_2 << endl;

  // scalar product
  cout << "[Test] Scalar product: (a,b,c) * k = (ak,bk,ck): ";
  cout << v_1 << " * 3 = " << v_1*3 << endl;
  cout << "[Test] Scalar product: k *(a,b,c) *  = (ak,bk,ck): 2 * ";
  cout << v_1 << " = " << 2*v_1 << endl;

  cout << endl << "Finish Test!!" << endl << endl;
  return EXIT_SUCCESS;
}
