// Copyright 2023 <Copyright Owner>
// Name: Wei-Mei(Katrina) Hsiung, Email: whsiung@uw.edu
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "SocketUtil.h"

#define BUFSIZE 1024
using std::cerr;
using std::endl;
using std::cout;
using std::string;

// Prints usage information about any failure
void Usage(char* progname);

int main(int argc, char** argv) {
  // Expect the port number as a command line argument.
  if (argc != 2) {
    Usage(argv[0]);
  }

  // Create the listening socket.
  int sock_family, listen_fd, client_fd;
  listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd == -1) {
    cerr << "Failed: listening socket on " << argv[1] << endl;
    Usage(argv[0]);
  }
  // Accepting a connection from a client
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    client_fd = accept(listen_fd,
                           reinterpret_cast<struct sockaddr*>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      if ((errno == EINTR) || (errno == EAGAIN))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << endl;
    }
    break;
  }
  // Loop, reading data until the client closes the connection.
  while (1) {
    unsigned char clientbuf[BUFSIZE];
    int res =  WrappedRead(client_fd, clientbuf, BUFSIZE);
    if (res == 0) {
      cout << " [The client disconnected.]" << endl;
      break;
    }

    if (res == -1) {
      cout << " [Error on client socket: ";
      cout << strerror(errno) << "]" << endl;
      close(client_fd);
      close(listen_fd);
      return EXIT_FAILURE;
    }
    string output(reinterpret_cast<char*>(clientbuf), res);
    cout << output;
  }

  close(client_fd);
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char* progname) {
  cerr << "usage: " << progname << " port" << endl;
  exit(EXIT_FAILURE);
}
