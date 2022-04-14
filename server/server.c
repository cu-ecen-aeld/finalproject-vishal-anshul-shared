/*

Author: Anshul Somani
Date: April 5 2022
Description: This code is used to read temperature and humidity values from Si7021 sensor breakout board	
			 from sparkfun. It reads both the values in no master hold mode and when the sensor is connected 
			 to the I2C-1 bus on BeagleBone Black. It then sends the sensor data from the server(BBB) to
			 the client (RPi). 
			 This code was used to test the server functionality for AESD final project Spring 2022
			 
This file uses server code written by Vishal Raj to implement Server socket communication.

*/

#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <syslog.h>
#include <errno.h>

#include <time.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>


#define SIZE 80
#define PORT 8080
#define SA struct sockaddr


/***********************************************************************************************
* Name          : func
* Description   : function for server- client communication 
* Parameters    : sockfd
* RETURN        : N/A
***********************************************************************************************/

float temp_RH_sensor(void)
{
	//TODO: use errno
	int ret_val =0;
	int i2c_fd;
	char *i2c_filename = "/dev/i2c-1"; 
	
	i2c_fd = open(i2c_filename, O_RDWR);
	if(i2c_fd <0)
	{
		syslog(LOG_ERR, "Call to open() failed. Error in accessing /dev/i2c-1\n\r");
		printf("Call to open() failed. Error in accessing /dev/i2c-1\n\r");
		return -1;
	}
	else
	{
		printf("Call to open() successful.\n\r");
	}
	
	//TODO: define the address as macros
	int sensor_addr = 0x40;
	
	ret_val = ioctl(i2c_fd, I2C_SLAVE, sensor_addr);
	if(ret_val <0)
	{
		syslog(LOG_ERR, "Call to ioctl() failed. Error in setting sensor address\n\r");
		printf("Call to ioctl() failed. Error in setting sensor address\n\r");
		return -1;
	}
	else
	{
		printf("Call to ioctl() successful.\n\r");
	}
	
	int reg = 0xF3;
	
	ret_val = write(i2c_fd, &reg, 1);
	if(ret_val != 1)
	{
		syslog(LOG_ERR, "Call to write() failed. Error in writing to temp sensor\n\r");
		printf("Call to write() failed. Error in writing to temp sensor\n\r");
		return -1;
	}
	else
	{
		printf("Call to write() successful.\n\r");
	}
	
	usleep(11000); //wait for atleast 10.8ms
	if(errno)
	{
		syslog(LOG_ERR, "Call to usleep() failed\n\r");
		printf("Call to usleep() failed\n\r");
	}
	
	int  n = 2;
	char buf[n];
	
	ret_val = read(i2c_fd, buf, n);
	if(ret_val != n)
	{
		syslog(LOG_ERR, "Call to read() failed. Error in reading from temp sensor\n\r");
		printf("Call to read() failed. Error in reading from temp sensor\n\r");
		return -1;
	}
	else
	{
		printf("Call to read() successful.\n\r");
	}
	
	int temp = buf[0];
	temp = temp<<8;
	temp |= buf[1];
	
	float temp_celcius = ((175.72*temp)/65536) - 46.85;
	syslog(LOG_DEBUG, "Temperature in celcius: %f", (float)temp_celcius);
	printf("Temperature in celcius: %f", (float)temp_celcius);
	
	return temp_celcius;
}

/***********************************************************************************************
* Name          : timer_handler
* Description   : function for SIGALRM handler 
* Parameters    : signal no.
* RETURN        : N/A
***********************************************************************************************/
/*static void timer_handler(int sig_no){

    //first store the local time in a buffer
    char time_string[200];
    time_t ti;
    struct tm *tm_ptr;
    int timer_len = 0;
     

    ti = time(NULL);
    tm_ptr = localtime(&ti);
    if(tm_ptr == NULL){
        perror("Local timer error!");
        exit(EXIT_FAILURE);
    }

    timer_len = strftime(time_string,sizeof(time_string),"timestamp:%d.%b.%y - %k:%M:%S\n",tm_ptr);
    if(timer_len == 0){
        perror("strftimer returned 0!");
        exit(EXIT_FAILURE);
    }

    printf("time value:%s\n",time_string);

    timer_up = 1;
    printf("timer_up_1:%d\r\n",timer_up);

} */
        
 /***********************************************************************************************
* Name          : Main
* Description   : Entry point function
* Parameters    : N/A
* RETURN        : N/A
***********************************************************************************************/
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    
    float temp_data;
    
    /*Registering SIGARM */
    //signal(SIGALRM,timer_handler);

    /*Timer handler part*/
   /*struct itimerval inter_timer;

    inter_timer.it_interval.tv_sec = 5; //timer interval of 10 secs
    inter_timer.it_interval.tv_usec = 0;
    inter_timer.it_value.tv_sec = 5; //time expiration of 10 secs
    inter_timer.it_value.tv_usec = 0;

    //arming the timer, choosing wall clock, not storing in old_value
    int tm_ret = setitimer(ITIMER_REAL, &inter_timer, NULL);
    if(tm_ret == -1){
        printf("timer error:%s\n",strerror(errno));
        syslog(LOG_DEBUG,"timer error:%s",strerror(errno));
    }*/


   
    // 1. create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    {
        printf("Error! socket() creation failed\n");
        exit(0);
    }
    else
    {
        printf("socket() creation succeeded \n");
    }
    bzero(&servaddr, sizeof(servaddr)); // reset string
   
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // 2. Bind the socket
    
    if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int))) == -1) {
        printf("socket opt failed...\n");
        exit(0);
    }
    else
        printf("Socket opt succeeded..\n");
        
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
    {
        printf("Error! bind() socket failed\n");
        exit(0);
    }
    else
    {
        printf("bind() socket succeeded\n");
    }
   
    // 3. Listen on the socket
    if ((listen(sockfd, 5)) != 0) 
    {
        printf("Error! Socket Listen failed\n");
        exit(0);
    }
    else
    {
         printf("Socket Listen succeeded. Server Listening..\n");
    }

    len = sizeof(cli);
   
    //4. Accept the socket  
    connfd = accept(sockfd, (SA*)&cli, (unsigned int *)&len);
    if (connfd < 0) 
    {
        printf("Error: accept() socket failed\n");
        exit(0);
    }
    else
    {
        printf("accept() socket succeeded\n");
    }
   
   int rt = 0;
   int length = 0;
   printf("Enter while()\n");
    //5. Call to function for server- client communication
    while(1)
    {
    	temp_data = temp_RH_sensor();
    	
    	length = snprintf(NULL, 0, "%f", temp_data);
    	char *str = malloc(length+1);
    	snprintf(str, length+1, "%f", temp_data);
    	
    	
    	printf("Sending temp data\n");
    	rt = write(sockfd, str, strlen(str)); // send the message to client
    	if(rt < 0)
    	{
            perror("Server_Error:");
        }
        else if(rt != strlen(str))
        {
            printf("partial sent bytes:%d\r\n",rt);
        }

        printf("sent bytes:%d\r\n",rt);
        free(str);
        
    	sleep(10);

    }
    printf("Exit while()\n");
    
    //6. Close the socket
    close(sockfd);
}
