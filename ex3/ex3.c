// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "Point3d.h"

#define x_val 10
#define y_val 20
#define z_val 30
#define scale 5

int main(int argc, char *argv[]) {
  // Test if Test_Point3d_Allocate can allocate
  // the new Point3D* with correct x,y,z successfully
  Point3d* ptr = Point3d_Allocate(x_val, y_val, z_val);
  if (ptr == NULL) {
    fprintf(stderr, "Failed: Point3d_Allocate return null.\n");
    return EXIT_FAILURE;
  }
  if (ptr->x != x_val || ptr->y != y_val || ptr->z != z_val) {
    fprintf(stderr, "Failed: Point3d_Scale not return the correct values.\n");
    free(ptr);
    return EXIT_FAILURE;
  }
  free(ptr);

  // Test if Point3d_Scale can scale the x,y,z correctly
  Point3d point = {x_val, y_val, z_val};

  Point3d_Scale(&point, scale);
  if (point.x != (x_val*scale) || point.y != (y_val*scale) ||
      point.z != (z_val*scale)) {
    return EXIT_FAILURE;
    fprintf(stderr, "Failed: Point3d_Scale not return the correct values.\n");
  }

  // Also need to test NULL case
  Point3d_Scale(NULL, 3);

  // Test if Point3d_GetOrigin can generate
  // the Origin Point3d successfully
  Point3d new_point = Point3d_GetOrigin();
  if (new_point.x || new_point.y || new_point.z) {
    return EXIT_FAILURE;
    fprintf(stderr, "Failed: Point3d_GetOrigin is not {0, 0, 0}.\n");
  }

  fprintf(stderr, "Congratulation! You Pass all tests successfully.\n");
  return EXIT_SUCCESS;
}
