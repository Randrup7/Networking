main : client_main.o server_main.o

client_main.o : client_socket.o 
	gcc -o client_main client_main.c client_socket.o 

server_main.o : server_socket.o echo.o
	gcc -o server_main server_main.c server_socket.o echo.o

client_socket.o :
	gcc -c client/client_socket.c

server_socket.o : 
	gcc -c server/server_socket.c 

echo.o :
	gcc -c server/echo.c

clean:
	rm client_main server_main *.o
