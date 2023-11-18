// Copyright 2023 <Copyright Owner>
// Name: Wei-Mei(Katrina) Hsiung, Email: whsiung@uw.edu
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* Declare the function to avoid build error */
void DumpBytes(void* data, int32_t byte_len);
void CopyAndSort(uint8_t unsorted[], uint8_t sorted[], int32_t byte_len);

int main(int argc, char *argv[]) {
  int32_t int_val = 1;
  float   float_val = 1.0f;
  uint8_t arr_unsorted[] = {3, 2, 0, 8, 17, 6, 10, 7, 8, 1, 12};
  uint8_t arr_sorted[]   = {0, 0, 0, 0,  0, 0,  0, 0, 0, 0,  0};

  DumpBytes(&int_val, sizeof(int_val));
  DumpBytes(&float_val, sizeof(float_val));
  DumpBytes(arr_unsorted, sizeof(arr_unsorted));
  CopyAndSort(arr_unsorted, arr_sorted, 11);
  DumpBytes(arr_sorted, sizeof(arr_sorted));

  return EXIT_SUCCESS;
}


// Print out the address and value of parameters called from main function.
void DumpBytes(void* data, int32_t byte_len) {
  uint8_t* arr = (uint8_t*)data;  // Create pointer to output the data
  printf("The %d bytes starting at 0x%p are", byte_len, data);
  for (int i = 0; i < byte_len; i++) {
    printf(" %02x", arr[i]);
  }
  printf("\n");
}


void CopyAndSort(uint8_t unsorted[], uint8_t sorted[], int32_t byte_len) {
  // (1) Call DumpBytes on the first array and its sizeof()
  DumpBytes(unsorted, sizeof(&unsorted));

  // (2) Using inserion sort to the first array in non-descending order
  for (int pos = 1; pos< byte_len; pos++) {
    int num = unsorted[pos];
    int prev = pos-1;
    while ((prev >= 0) && (unsorted[prev] > num)) {
       unsorted[prev+1] = unsorted[prev];
       prev--;
    }
    unsorted[prev+1] = num;
  }

  // (3) Copy to the sorted array
  for (int i = 0; i < byte_len; i++) {
    sorted[i] = unsorted[i];
  }
}
