// Copyright 2023 <Copyright Owner>
// Name: Wei-Mei(Katrina) Hsiung, Email: whsiung@uw.edu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please correct format: ex1.exe (int)\nExample: ex1.exe 100\n");
        return EXIT_FAILURE;
    }

    // Error condition for end pointer of vail integer
    // which is not the same with the argv[1] end address.
    char* ptr;
    int input = strtol(argv[1], &ptr, 10);
    if (*ptr != '\0') {
        printf("Please correct format: ex1.exe (int)\nExample: ex1.exe 100\n");
        return EXIT_FAILURE;
    }

    // Adding terms 0 through n
    double pi = 3.0;
    for (int n = 1 ; n <= input; n++) {
        double num = (double)4/(2*n*(2*n+1)*(2*n+2));
        if ((n%2)==0) num*=-1;
        pi += num;
    }

    printf("Our estimate of Pi is %.20f\n", pi);
    return EXIT_SUCCESS;
}
