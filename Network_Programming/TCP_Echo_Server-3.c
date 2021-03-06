#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "mysock.h"
#define SERV_PORT 9877
#define LISTENQ 1024
int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = Socket(PF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = PF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));



	Listen(listenfd, LISTENQ);
	Signal(SIGCHLD, sig_chld);
	for ( ; ; ) 
	{
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
		if((childpid = Fork()) == 0) 
		{
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		} //if
		Close(connfd);
	} //for
} // main

