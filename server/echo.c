#include <stdio.h>
#include <sys/socket.h>

#define MAXLINE 2000

void echo(int conn_fd) {

  int read_size;
  char client_msg[MAXLINE];

  while ((read_size = recv(conn_fd, client_msg, MAXLINE, 0)) > 0) {
    // write back to conn_fd
		fprintf(stdout, "Received from client: %s", client_msg);
    send(conn_fd, client_msg, MAXLINE, 0);
  }
	
}
