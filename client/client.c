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
#include <string.h>
#include <pthread.h>

//#define SERVICE_PORT "8080"
#define SIZE 80
#define PORT 8080
#define SA struct sockaddr

#define TEMP_TAG_POS		0
#define TEMP_SIZE			5
#define TEMP_BUFF_SIZE		6
#define TEMP_DATA_OFFSET	2

#define HUM_TAG_POS			8
#define HUM_SIZE			4
#define HUM_BUFF_SIZE		5	
#define HUM_DATA_OFFSET		10				

char temp_buff[TEMP_BUFF_SIZE] = {0};
char hum_buff[HUM_BUFF_SIZE] = {0};

int socket_fd =0;

char *file_path_tmp = "/var/tmp/tmp-socket-data.txt";
char *file_path_hum = "/var/tmp/hum-socket-data.txt";

char buffer[SIZE];

void parse_data(char *buffer);
void write_to_file(char *temp_buff, char *hum_buff);

/*struct addrinfo hints;
struct addrinfo *servinfo;
struct sockaddr_storage servinfo_connectingaddr; //to store connecting address from accept()
socklen_t addr_size;

const char *service_port = SERVICE_PORT;

char ip_addr[INET_ADDRSTRLEN];*/
struct sockaddr_in servaddr;

int errnum = 0;
int ret_val;

void socket_open(int sockfd)
{
	memset(buffer, 0 , sizeof(buffer));

    while(1) {

        bzero(buffer, sizeof(buffer));
        while(read(sockfd, buffer, sizeof(buffer))==0);  // read client message and copy that in the buffer
        printf("From Server : %s\n\r", buffer);

        parse_data(buffer);
    }

}


void parse_data(char *buffer)
{
	int i;
	char *tp = buffer;
	char *hp = buffer;

	if(*(tp + TEMP_TAG_POS) == 'T'){

		for(i=0; i < TEMP_SIZE; i++){
			temp_buff[i] = *(tp + i + TEMP_DATA_OFFSET);
		}

		temp_buff[i] = '\0';
	}

	if(*(hp + HUM_TAG_POS) == 'H'){

		for(i=0; i < HUM_SIZE; i++){
			hum_buff[i] = *(hp + i + HUM_DATA_OFFSET);
		}

		hum_buff[i] = '\0';
	}

	write_to_file(temp_buff, hum_buff);
}

void write_to_file(char *temp_buff, char *hum_buff)
{

    /*Open the temp file for writing*/
    int fd = open(file_path_tmp, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if(fd == -1){
		printf("File open error for appending\n");
		perror("File_Open:");
		exit(EXIT_FAILURE);
	}

    /*Write data to the temp file*/
    int nr = write(fd,temp_buff,strlen(temp_buff));
	if(nr == -1){
		printf("Error: File could not be written!\n");
		//syslog(LOG_ERR,"Error: File could not be written!");
		exit(EXIT_FAILURE);
	}else if(nr != strlen(temp_buff)){
		printf("Error: File partially written!\n");
		//syslog(LOG_ERR,"Error: File partially written!");
		exit(EXIT_FAILURE);
	}

	close(fd);

	/*Open the hum file for writing*/

	fd = open(file_path_hum, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if(fd == -1){
		printf("File open error for appending\n");
		perror("File_Open:");
		exit(EXIT_FAILURE);
	}

    /*Write data to the hum file*/
    nr = write(fd,hum_buff,strlen(hum_buff));
	if(nr == -1){
		printf("Error: File could not be written!\n");
		//syslog(LOG_ERR,"Error: File could not be written!");
		exit(EXIT_FAILURE);
	}else if(nr != strlen(hum_buff)){
		printf("Error: File partially written!\n");
		//syslog(LOG_ERR,"Error: File partially written!");
		exit(EXIT_FAILURE);
	}

	close(fd);

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
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
	printf("***Starting client program Version 127.0...***\n");

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
		socket_open(socket_fd);     // function for chat
		
		

/******************************************************

	 close()
	
******************************************************/
	
	//TODO: Error Checking
	close(socket_fd);
	
}
