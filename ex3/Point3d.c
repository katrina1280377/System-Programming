// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Point3d.h"

// Allocate memory tp Point3d and assign the three arguments to the x, y, and z.
Point3d* Point3d_Allocate(int32_t x, int32_t y, int32_t z) {
  Point3d* ptr = (Point3d*)malloc(sizeof(Point3d));
  if (ptr == NULL) return NULL;
  ptr->x = x;
  ptr->y = y;
  ptr->z = z;
  return ptr;
}

// Scales the x, y, and z fields of the pointed-to struct by the given value
void Point3d_Scale(Point3d* ptr, int32_t argu) {
  if (ptr != NULL) {
    ptr->x  *= argu;
    ptr->y  *= argu;
    ptr->z  *= argu;
  }
}

// Constructs a Point3d with x, y, and z equal to zero
Point3d Point3d_GetOrigin() {
  Point3d new_point = {0, 0, 0};
  return new_point;
}
