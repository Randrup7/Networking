client_socket:
	gcc client/client_socket.c -o client_socket

server_socket :
	gcc server/server_socket.c - o server_socket

main : client_socket server_socket
	gcc client_main.c -o main

clean:
	rm getaddrinfo
