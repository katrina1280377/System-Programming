// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu

#include <iostream>
#include <cstdlib>
#include "Vector.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char** argv) {
  int n;

  // Scan the user input
  cout << "Please enter a positive integer to factorize: ";
  cin >> n;

  // Error Condition
  if (!cin || (n <= 0)) {
    cerr << "Please input an integer > 0" << endl;
    return EXIT_FAILURE;
  }

  // Check factor from 1 to num to see if they are
  for (int i = 1; i <= n; i++) {
    if (n % i == 0) {
      if (i == 1) {
        cout << i;
      } else {
        cout << " " << i;
      }
    }
  }

  cout << endl;
  return EXIT_SUCCESS;
}
