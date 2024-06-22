main : client_main.c client_socket.o server_socket.o
	gcc -o client_main client_main.c client_socket.o server_socket.o

client_socket.o :
	gcc -c client/client_socket.c

server_socket.o : 
	gcc -c server/server_socket.c 

clean:
	rm client_main *.o
