
// Copyright 2023 <Copyright Owner>
// Name: Wei-Mei(Katrina) Hsiung, Email: whsiung@uw.edu
#include "SocketUtil.h"

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include <iostream>

using std::cerr;
using std::endl;


int Listen(char* portnum, int* sock_family) {
  // Hints addrinfo structure
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET6;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_flags |= AI_V4MAPPED;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;

  struct addrinfo* result;
  int res = getaddrinfo(nullptr, portnum, &hints, &result);
  if (res != 0) {
    std::cerr << "getaddrinfo() failed: ";
    std::cerr << gai_strerror(res) << std::endl;
    return -1;
  }

  // Loop through the returned address structures
  int listen_fd = -1;
  for (struct addrinfo* rp = result; rp != nullptr; rp = rp->ai_next) {
    listen_fd = socket(rp->ai_family,
                       rp->ai_socktype,
                       rp->ai_protocol);
    if (listen_fd == -1) {
      // Creating this socket failed. Loop to the next and try again
      std::cerr << "socket() failed: " << strerror(errno) << std::endl;
      continue;
    }

    // Configure the socket
    int optval = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof(optval));

    // Try binding the socket to the address and port number
    if (bind(listen_fd, rp->ai_addr, rp->ai_addrlen) == 0) {
      *sock_family = rp->ai_family;
      break;
    }

    // The bind failed.  Close the socket, then loop back
    close(listen_fd);
    listen_fd = -1;
  }

  freeaddrinfo(result);

  // If we failed to bind, return failure.
  if (listen_fd <= 0) {
    cerr << "Couldn't bind to any addresses. " << endl;
    return listen_fd;
  }

  // Success. Tell the OS that we want this to be a listening socket.
  if (listen(listen_fd, SOMAXCONN) != 0) {
    cerr << "Failed to mark socket as listening: ";
    cerr << strerror(errno) << endl;
    close(listen_fd);
    return -1;
  }

  // Return to the client the listening file descriptor.
  return listen_fd;
}

int WrappedRead(int fd, unsigned char* buf, int readlen) {
  // Read from the socket
  int bytesRead = read(fd, buf, readlen);
  while (1) {
    if (bytesRead == -1) {
      cerr << "Error reading from socket" << endl;
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;
    }
    break;
  }
  return bytesRead;
}

int WrappedWrite(int fd, unsigned char* buf, int writelen) {
    // Write to the socket
    int bytesWritten = write(fd, buf, writelen);
    if (bytesWritten == -1) {
        cerr << "Error writing to socket" << endl;
    }
    return bytesWritten;
}
