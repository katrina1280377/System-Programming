// Copyright 2023 <Copyright Owner>
// Name: Wei-Mei(Katrina) Hsiung, Email: whsiung@uw.edu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

#include "SocketUtil.h"

using std::cerr;
using std::endl;

int main(int argc, char** argv) {
  if (argc != 4) {
    cerr << "Please use correct format, example:" << endl;
    cerr << " ./ex10 localhost 5555 test.txt" << endl;
    exit(EXIT_FAILURE);
  }

  // Open the file
  int file = open(argv[3], O_RDONLY);
  if (file == -1) {
    cerr << "Failed: open the file" << endl;
    exit(EXIT_FAILURE);
  }

  unsigned int port = 0;
  if (sscanf(argv[2], "%d", &port) != 1) {
    close(file);
    cerr << "Failed: open the file" << endl;
    exit(EXIT_FAILURE);
  }

  // Get sockaddr structure.
  struct sockaddr_storage address;
  size_t len;
  if (!LookupName(argv[1], port, &address, &len)) {
    close(file);
    cerr << "Failed to get sockaddr structure" << endl;
  }

  // Connect the host
  int socket;
  if (!Connect(address, len, &socket)) {
    close(file);
    cerr << "Failed to connect the host" << endl;
    exit(EXIT_FAILURE);
  }

  // Read input file & write socket.
  unsigned char readbuf[256];
  while (1) {
    int res = WrappedRead(file, readbuf, 256);
    if (res == 0)
      break;
    if (res < 0) {
      close(socket);
      close(file);
      return EXIT_FAILURE;
    }
    if (WrappedWrite(socket, readbuf, res) != res) {
      close(socket);
      close(file);
      return EXIT_FAILURE;
    }
  }

  // Close file & socket
  close(socket);
  close(file);
  return EXIT_SUCCESS;
}
