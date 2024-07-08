server_files := server_socket.o echo.o
exe_files := client_main server_main process_server_main thread_server_main IOMult_server_main

main : client_main.o server_main.o process_server_main.o

client_main.o : client_socket.o 
	gcc -o client_main client_main.c client_socket.o 

server_main.o : ${server_files}
	gcc -o server_main server_main.c ${server_files}

process_server_main.o : ${server_files}
	gcc -o process_server_main concurrency/process_concurrent_server.c ${server_files}

client_socket.o :
	gcc -c client/client_socket.c

server_socket.o : 
	gcc -c server/server_socket.c 

echo.o :
	gcc -c server/echo.c

clean:
	rm ${exe_files} *.o
