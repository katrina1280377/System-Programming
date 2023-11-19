// Copyright 2023 <Copyright Owner>
// Name: Wei-Mei(Katrina) Hsiung, Email: whsiung@uw.edu#include "SocketUtil.h"
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "SocketUtil.h"

using std::cerr;
using std::endl;

bool LookupName(char* name,
                unsigned short port,
                struct sockaddr_storage* ret_addr,
                size_t* ret_addrlen) {
  // Set up the server address struct
  struct addrinfo addr_in, *result;
  memset(&addr_in, 0, sizeof(addr_in));
  // Use AF_UNSPEC for both IPv4 and IPv6
  addr_in.ai_family = AF_UNSPEC;
  addr_in.ai_socktype = SOCK_STREAM;
  // Use getaddrinfo to perform hostname resolution
  int status = getaddrinfo(name, nullptr, &addr_in, &result);
  if (status != 0) {
    cerr << "getaddrinfo error: " << gai_strerror(status) << endl;
    return false;
  }

  if (result->ai_family == AF_INET) {
    struct sockaddr_in* v4_addr;
    v4_addr = reinterpret_cast<struct sockaddr_in*>(result->ai_addr);
    v4_addr->sin_port = htons(port);
  } else if (result->ai_family == AF_INET6) {
    struct sockaddr_in6* v6_addr;
    v6_addr = reinterpret_cast<struct sockaddr_in6*>(result->ai_addr);
    v6_addr->sin6_port = htons(port);
  } else {
    cerr << "Failed on IPv4 or IPv6 address" << endl;
    freeaddrinfo(result);
    return false;
  }
  // Copy the first result to ret_addr
  memcpy(ret_addr, result->ai_addr, result->ai_addrlen);
  *ret_addrlen = result->ai_addrlen;
  // Free the result structure
  freeaddrinfo(result);
  return true;
}

bool Connect(const struct sockaddr_storage& addr,
             const size_t& addrlen,
             int* ret_fd) {
  // Create a TCP socket
  int sockfd = socket(addr.ss_family, SOCK_STREAM, 0);
  if (sockfd == -1) {
      cerr << "Error opening socket" << endl;
      return false;
  }
  // Connect to the server
  if (connect(sockfd, reinterpret_cast<const sockaddr*>(&addr)
      , addrlen) == -1) {
      cerr << "Error connecting to server" << endl;
      close(sockfd);
      return false;
  }
  *ret_fd = sockfd;
  return true;
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
