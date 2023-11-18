// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu
#include <stdio.h>    // for snprintf
#include <stdlib.h>   // for EXIT_SUCCESS, NULL
#include <string.h>   // for strrchr, strcmp, strlen
#include <stdbool.h>  // for bool
#include <dirent.h>   // for direction function

#include "ro_file.h"


/*** HELPER FUNCTION DECLARATIONS ******************************************/

// Returns EXIT_FAILURE can free memory when there is any error.
int ErrorCase(DIR* dir, char* full_path);

// Returns whether or not a filename ends in ".txt".
bool IsTxtFile(char* filename);

// Concatenate the directory and file names into a full path. The caller is
// responsible for freeing the allocated string. Exits if an error occurs.
char* Concatenate(char* dirname, char* filename);

/*
 * This program:
 * - Accepts a directory name as a command-line argument.
 * - Scans through the directory looking for all files whose names end with
 *   the four characters ".txt".
 * - For every such file found, write the contents of those files to stdout
 *   without adding any additional characters or formatting.
 *   Eventually reading the files with ro_file module.
 */
int main(int argc, char** argv) {
  // If it is not the correct format, return error
  if (argc != 2) {
    printf("Correct format: ./ex4 directory_name\n");
    printf("Example: ./ex4 .\n");
    return EXIT_FAILURE;
  }

  DIR* dir = opendir(argv[1]);
  if (dir == NULL) {
      perror("Unable to open directory\n");
      return EXIT_FAILURE;
  }

  struct dirent* entry =  readdir(dir);
  // Traversal the directory by its entries
  while (entry != NULL) {
    // Check if the entry is a regular txt file by helper function
    if (IsTxtFile(entry->d_name)) {
      printf("\n**** File Name: %s ****\n", entry->d_name);
      char* full_path = Concatenate(argv[1], entry->d_name);
      // Open the file with ro_file module
      RO_FILE* file = ro_open(full_path);
      if (file == NULL) {
          perror("ro_file failed!\n");
          return ErrorCase(dir, full_path);
      }
      char buffer[1024];
      ssize_t bytes_read = ro_read(buffer, 1024, file);

      // Reading the file
      while (bytes_read > 0) {
        // Print the text we read.
        if (fwrite(buffer, 1, bytes_read, stdout) != bytes_read) {
          perror("fwrite failed!\n");
          ro_close(file);
          return ErrorCase(dir, full_path);
        }
        bytes_read = ro_read(buffer, 1024, file);
      }
      // Error in the ro_read function
      if (bytes_read < 0) {
        perror("ro_read failed!\n");
        ro_close(file);
        return ErrorCase(dir, full_path);
      }
      if (ro_close(file) != 0) {
        perror("ro_close failed!\n");
        return ErrorCase(dir, full_path);
      }
      free(full_path);
      printf("\n");
    }
    entry =  readdir(dir);
  }

  closedir(dir);
  return EXIT_SUCCESS;
}


/*** HELPER FUNCTION DEFINITIONS *******************************************/

bool IsTxtFile(char* filename) {
  char* dot = strrchr(filename, '.');
  return dot && !strcmp(dot, ".txt");
}

char* Concatenate(char* dirname, char* filename) {
  bool has_trailing_slash = dirname[strlen(dirname) - 1] == '/';
  // Concatenate directory and file name.
  size_t dlen = strlen(dirname);
  size_t flen = strlen(filename);
  // Malloc space for full path name:
  // dlen + strlen("/") + flen + strlen('\0') = dlen + flen + 2
  int size_to_malloc = has_trailing_slash ? dlen + flen + 1 : dlen + flen + 2;
  char* fullpath = (char*) malloc(sizeof(char) * (size_to_malloc));
  if (fullpath == NULL) {
    fprintf(stderr, "Error on malloc.\n");
    exit(EXIT_FAILURE);
  }
  if (has_trailing_slash) {
    snprintf(fullpath, size_to_malloc, "%s%s", dirname, filename);
  } else {
    snprintf(fullpath, size_to_malloc, "%s/%s", dirname, filename);
  }
  return fullpath;
}

int ErrorCase(DIR* dir, char* full_path) {
  free(full_path);
  closedir(dir);
  return EXIT_FAILURE;
}
