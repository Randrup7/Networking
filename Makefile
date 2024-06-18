getaddrinfo :
	gcc getaddrinfo.c -o getaddrinfo

server_socket :
	gcc server_socket.c - o server_socket

clean:
	rm getaddrinfo
