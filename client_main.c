#include "client/client_socket.h"
#include "server/server_socket.h"
#include "stdio.h"

int main(int argc, char *argv[]) {

	int client_fd = open_clientfd(argv[1], argv[2]);
	printf("%d\n", client_fd);
	return 0;
}
