// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::string;
using std::map;

// Helper template function
template <typename T> bool ReadValue(ifstream& in, T* const output);

int main(int argc, char** argv) {
  // format check
  if (argc != 2) {
    cerr << "Please use correct format: ./ex8 filename" << endl;
    return EXIT_FAILURE;
  }
  // open file
  ifstream file(argv[1], ifstream::in);
  if (!file) {
    cerr << "Cannot open " << argv[1] << endl;
    return EXIT_FAILURE;
  }

  // read the file and create map table to count
  string str;
  map<string, size_t> table;
  while (ReadValue<string>(file, &str)) {
    table[str]++;
  }

  // print out the values in files
  for (const auto& str : table) {
    cout << str.first << ", " << str.second << endl;
  }

  return EXIT_SUCCESS;
}

template <typename T> bool ReadValue(ifstream& in, T* const output) {
  T value;
  in >> value;
  if (in.fail()) {
    return false;
  }
  *output = value;
  return true;
}
