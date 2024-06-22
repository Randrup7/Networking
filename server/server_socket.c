#include "server_socket.h"
#include <netdb.h>
#include <string.h> // memset
#include <sys/socket.h>
#include <unistd.h>

int open_listenfd(char *port) {
  struct addrinfo hints, *res, *iter;
  int listen_fd;
	int optval = 1; // Used in setsockopt

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;             // accept connections
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; // any IP address
  hints.ai_flags |= AI_NUMERICSERV;            // any port

  getaddrinfo(NULL, port, &hints, &res);

  // loop through result
  for (iter = res; iter; iter = iter->ai_next) {
    // Create socket file descriptor
    if ((listen_fd =
             socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol)) < 0)
      continue; // move to next addrinfo
		
		/* avoid getting socket alreadyu in use error */
		setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));

    if (bind(listen_fd, iter->ai_addr, iter->ai_addrlen) == 0)
      break; // connect successfull

    close(listen_fd);	
  }

	freeaddrinfo(res);
	if (!iter) {
		return -1;	
	}
	if (listen(listen_fd, 5) < 0) {
		close(listen_fd);
		return -1;
	}

  return listen_fd;
}
