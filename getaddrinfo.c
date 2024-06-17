#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  // hints is an addrinfo filtering possible result addrinfos
  // res is a ptr to an addrinfo
  // It is a linked list to all relevant sockets.
  // socket() and connect() will try all entries in list untill a connection is
  // established
  struct addrinfo hints, *res, *iter;

  // setting the hints addrinfo
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;					// both IPv4 and v6 allowed 
  hints.ai_socktype = SOCK_STREAM; //

  int error = getaddrinfo(argv[1], 0, &hints, &res);
  if (!error)
  {
	char buf[100];
	for (iter = res; iter; iter = iter->ai_next)
	{
		getnameinfo(iter->ai_addr, iter->ai_addrlen, buf, 100, NULL, 0, NI_NUMERICHOST);
		printf("%s\n", buf);
	}
  }
  // This socket is a connection end point
  // AF_INET indicates 32-bit IP-address
  // SOCK_STREAM indicates end point for connection
  //int clientfd;
  //clientfd = socket(AF_INET, SOCK_STREAM, 0);

  // Call connect()

  // Call

  freeaddrinfo(res);

  return 0;
}
