#include <netdb.h>		// addrinfo
#include <string.h>		// memset
#include <sys/socket.h>	// addrinfo, socket, connect
#include <sys/types.h>
#include <unistd.h>		// close

int open_clientfd(char *hostname, char *port) {
  // hints is an addrinfo filtering possible result addrinfos
  // res is a ptr to an addrinfo
  // It is a linked list to all relevant sockets.
  // socket() and connect() will try all entries in list untill a connection is
  // established
  struct addrinfo hints, *res, *iter;
  int clientfd;

  // setting the hints addrinfo
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;     // both IPv4 and v6 allowed
  hints.ai_socktype = SOCK_STREAM; // TCP

  getaddrinfo(hostname, port, &hints, &res);

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

  // Clean up
  freeaddrinfo(res);
  if (!iter) { // If all connections failed
    return -1;
  } else {
    return clientfd;
  }
}

