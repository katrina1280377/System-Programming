// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu
#ifndef POINT3D_H_
#define POINT3D_H_
#include <inttypes.h>

// Define a new structured type called Point3d
// which contains int32_t fields for x, y, and z coordinates.
typedef struct point3d_st {
  int32_t x;
  int32_t y;
  int32_t z;
} Point3d;

// Allocate memory tp Point3d and assign the three arguments to the x, y, and z.
Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z);

// Scales the x, y, and z fields of the pointed-to struct by the given value
void Point3d_Scale(Point3d* ptr, int32_t argu);

// Constructs a Point3d with x, y, and z equal to zero
Point3d Point3d_GetOrigin();

#endif  // POINT3D_H_
