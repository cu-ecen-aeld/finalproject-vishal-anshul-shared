/*

Author: Anshul Somani
Date: April 8 2022
Description: This code was used to test the client functionality for AESD final project Spring 2022
			 It's supposed to print dummy strings received from the server.
			

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "errno.h"
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 80
#define PORT 8080
#define SA struct sockaddr

int socket_fd =0;
struct sockaddr_in servaddr;

int errnum =0;
int ret_val;

void func(int sockfd)
{
    char buffer[SIZE];
    while(1) {
        bzero(buffer, sizeof(buffer));
        while(read(sockfd, buffer, sizeof(buffer))==0);  // read client message and copy that in the buffer
        printf("From Server : %s\n\r", buffer);
    }
}

int setup_comm()
{

/******************************************************
	socket()
	
******************************************************/
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		errnum = errno;
		syslog(LOG_ERR, "Unable to create the socket. The error was %s\n", strerror(errnum));
		
		printf("Error: Unable to create socket %d\n\r", errnum);
		return -1;
	}
	
	
/******************************************************
	connect()
	
******************************************************/

	memset(&servaddr, 0, sizeof(servaddr));
	
	/* Assign IP and port */
	servaddr.sin_addr.s_addr = inet_addr("10.0.0.34");
	servaddr.sin_family = AF_INET;  
	servaddr.sin_port = htons(PORT);
	
	/* Create connection between the client socket and server socket */
	ret_val = connect(socket_fd, (SA*)&servaddr, sizeof(servaddr));
	if(ret_val != 0)
	{
		errnum = errno;
		syslog(LOG_ERR, "connect() returned error. The error was %s\n", strerror(errnum));
		
		printf("Error: connect() returned error %d\n\r", errnum);
		return -1;
	}
	return 0;
}

int main()
{
	/*Start syslog daemon*/
    openlog("client", LOG_USER, LOG_DEBUG|LOG_ERR); 
   
	
/******************************************************
	 Setup_comm()
	
******************************************************/
	if(setup_comm() == -1)
	{
		return -1;
	}
	
	
/******************************************************
	  Perform task
	
******************************************************/	

		syslog(LOG_DEBUG, "Connected to server\n");	
		printf("Connected to server\n\r");
		func(socket_fd);     // function for chat
		
		

/******************************************************
	 close()
	
******************************************************/
	
	close(socket_fd);
	
}
