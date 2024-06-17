#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  // hints is an addrinfo filtering possible result addrinfos
  // res is a ptr to an addrinfo
  // It is a linked list to all relevant sockets.
  // socket() and connect() will try all entries in list untill a connection is
  // established
  struct addrinfo hints, *res, *iter;
  int getaddrstatus;
  int clientfd;

  // setting the hints addrinfo
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;     // both IPv4 and v6 allowed
  hints.ai_socktype = SOCK_STREAM; // TCP

  // Error check on getaddrinfo
  if ((getaddrstatus = getaddrinfo(argv[1], 0, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(getaddrstatus));
    exit(EXIT_FAILURE);
  }

  // Loop over results from getaddrinfo
  for (iter = res; iter; iter = iter->ai_next) {
    // Create socket file descriptor
    if ((clientfd =
             socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol)) < 0)
      continue; // move to next addrinfo

    // Connect to clientfd
    if (connect(clientfd, iter->ai_addr, iter->ai_addrlen) != -1)
      break; // connect successfull

    close(clientfd);
  }

  // This socket is a connection end point
  // AF_INET indicates 32-bit IP-address
  // SOCK_STREAM indicates end point for connection
  // int clientfd;
  // clientfd = socket(AF_INET, SOCK_STREAM, 0);

  // Call connect()

  // Call

  freeaddrinfo(res);

  return 0;
}
