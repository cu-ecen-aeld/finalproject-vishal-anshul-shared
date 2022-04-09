//TODO: File Header

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

//#define SERVICE_PORT "8080"
#define SIZE 80
#define PORT 8080
#define SA struct sockaddr

int socket_fd =0;

/*struct addrinfo hints;
struct addrinfo *servinfo;
struct sockaddr_storage servinfo_connectingaddr; //to store connecting address from accept()
socklen_t addr_size;

const char *service_port = SERVICE_PORT;

char ip_addr[INET_ADDRSTRLEN];*/
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

	signal()
	
******************************************************/
	/*signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	//signal(SIGKILL, sig_handler);
	signal(SIGALRM, alarm_handler);*/
	//TODO: Enable Signals in the end
	
/******************************************************

	 Setup_comm()
	
******************************************************/
	if(setup_comm() == -1)
	{
		return -1;
	}
	
	
/******************************************************

	 //TODO: Perform task
	
******************************************************/	

		syslog(LOG_DEBUG, "Connected to server\n");	
		printf("Connected to server\n\r");
		func(socket_fd);     // function for chat
		
		

/******************************************************

	 close()
	
******************************************************/
	
	//TODO: Error Checking
	close(socket_fd);
	
}
