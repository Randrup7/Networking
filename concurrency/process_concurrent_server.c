#include "../server/echo.h"
#include "../server/server_socket.h"

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXLINE 2000

// This signal child handler 
void sig_chld_handler(int sig)
{
	while (waitpid(-1, 0, WNOHANG) > 0);
	return;
}

int main(int argc, char *argv[]) {

  // Declaring variables
  int listen_fd;
  int conn_fd;
  socklen_t clientlen;
  char client_hostname[MAXLINE];
  char client_port[MAXLINE];

  // using sockaddr_storage makes sure we have space for any address
  struct sockaddr_storage clientaddr;

  clientlen = sizeof(struct sockaddr_storage);
  // Port number to be listened to must be specified
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  listen_fd = open_listenfd(argv[1]);
  if (listen_fd == -1) {
    puts("Could not start server");
    exit(0);
  }

  while (1) {

    puts("Listening for incoming connections...\n");
    // Accept incoming connection and place client sockaddr in clientaddr
    conn_fd = accept(listen_fd, (struct sockaddr *)&clientaddr, &clientlen);

    // retreiving client hostname and port from clientaddr
    getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostname,
                MAXLINE, client_port, MAXLINE, 0);

    printf("Connected to (%s, %s)\n", client_hostname, client_port);

    if (fork() == 0) {
			close(listen_fd); // Close as this process is not listening
      echo(conn_fd);
			close(conn_fd);
			exit(0); // Exit this process
    }

    //puts("Closing connection");
    close(conn_fd);
  }

  return 0;
}
