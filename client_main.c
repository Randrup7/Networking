#include "client/client_socket.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 2000

int main(int argc, char *argv[]) {

  int client_fd;
  char *host;
  char *port;
  char buf[MAXLINE];
	char server_reply[MAXLINE];

  if (argc != 3) {
    fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
    exit(0);
  }

	host = argv[1];
	port = argv[2];

  if ((client_fd = open_clientfd(argv[1], argv[2])) == -1) {
		fputs("Could not connect to server", stderr);
		exit(0);
	};

	puts("Connected to server");

	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (send(client_fd, buf, MAXLINE, 0) < 0) {
			puts("send error");
			break;
		};

		memset(buf, 0, MAXLINE);
		if (recv(client_fd, buf, MAXLINE, 0) < 0) {
			fputs("recv failed.\n", stderr);
			break;
		};

		fputs(buf, stdout);

	}

  close(client_fd);
  return 0;
}
