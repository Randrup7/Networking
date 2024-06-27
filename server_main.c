#include "server/server_socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define MAXLINE 2000

int main(int argc, char* argv[]) {

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
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	
	listen_fd = open_listenfd(argv[1]);
	puts("Listening for incoming connections");

//	while (1) {
		// Accept incoming connection and place client sockaddr in clientaddr
		conn_fd = accept(listen_fd, (struct sockaddr *)&clientaddr, &clientlen);

		// retreiving client hostname and port from clientaddr
		getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostname, MAXLINE, 
						client_port, MAXLINE, 0);
		
		printf("Connected to (%s, %s)", client_hostname, client_port);

		close(conn_fd);
//	}


	return 0; 
}
