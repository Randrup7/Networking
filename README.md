# Networking
This is simply a small repo where I test out the C Socket API.

## Files
The source files related to the client side are:
- client_main.c
- client/client_socket.c

The source files related to the server side are:
- server_main.c
- server/echo.c
- server/server_socket.c

## Build / Compile / Run
Run Make in the repo. This creates object files and two executables: server_main and client_main 
Firstly run the server_main with a listening port as input:
'''console
./server_main 1234
'''
In another shell, simultaneously run client_main with an IP and port:
'''console
./server_main 127.0.0.1 1234
'''

The client should now connect to the server, and the client can type input and the server will echo it back.

## Other
Also testing using git from the terminal and my new NeoVim setup
