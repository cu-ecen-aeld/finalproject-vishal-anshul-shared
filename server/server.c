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

#define TSL2591_GAIN_MED (0x10) // Medium gain (25x)
#define COMMAND_BIT (0xA0)
#define REGISTER_CTRL (0x01)
#define INTEGRATION_300MS (0x02)
#define REG_CHAN0_LOW (0x14)
#define REG_CHAN1_LOW (0x16)
#define REGISTER_ENABLE (0x00)
#define TSL2591_ENABLE_POWERON (0x01)
#define TSL2591_ENABLE_AEN (0x02)
#define TSL2591_ENABLE_AIEN (0x10)
#define TSL2591_ENABLE_NPIEN (0x80)

struct data_s{

	float temp_celcius_data;
	float rel_humidity_data;
	unsigned int ir_light_data;
	unsigned int visible_light_data;
	unsigned int full_light_data;

};


struct data_s sensor_data;

/***********************************************************************************************
* Name          : temp_readings
* Description   : Reads the temperature from Si7021
* Parameters    : void
* RETURN        : float
***********************************************************************************************/

void light_readings(void)
{
	int errnum;
	int ret_val =0;
	int i2c_fd;
	char *i2c_filename = "/dev/i2c-1"; 
	
	i2c_fd = open(i2c_filename, O_RDWR);
	if(i2c_fd <0)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to open() failed. Error in accessing /dev/i2c-1 %d\n\r", errnum);
		printf("Call to open() failed. Error in accessing /dev/i2c-1 %d\n\r", errnum);
		//return -1;
	}
	else
	{
		printf("Call to open() successful.\n\r");
	}
	
	int sensor_addr = 0x29;
	
	ret_val = ioctl(i2c_fd, I2C_SLAVE, sensor_addr);
	if(ret_val <0)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to ioctl() failed. Error in setting sensor address %d\n\r", errnum);
		printf("Call to ioctl() failed. Error in setting sensor address %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to ioctl() successful.\n\r");
	}
	
	/******************************************
	*
	* Enable Sensor
	*
	******************************************/
	
	int  n = 2;
	char buf[n];
	
	buf[0] = (COMMAND_BIT|REGISTER_ENABLE);
	buf[1] = (TSL2591_ENABLE_POWERON|TSL2591_ENABLE_AEN|TSL2591_ENABLE_AIEN|TSL2591_ENABLE_NPIEN);
	
	ret_val = write(i2c_fd, &buf, 2);
	if(ret_val != 2)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to write() failed. Error in enabling light sensor %d\n\r", errnum);
		printf("Call to write() failed. Error in enabling light sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to write() to enable light sensor successful\n\r");
	}
	
	
	/******************************************
	*
	* Set Gain 
	*
	******************************************/

	
	buf[0] = (COMMAND_BIT|REGISTER_CTRL);
	buf[1] = (TSL2591_GAIN_MED);
	
	ret_val = write(i2c_fd, &buf, 2);
	if(ret_val != 2)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to write() failed. Error in setting gain for light sensor %d\n\r", errnum);
		printf("Call to write() failed. Error in setting gain for light sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to write() to set gain successful. Gain set to 25x\n\r");
	}
	
	/******************************************
	*
	* Set Timing 
	*
	******************************************/
	
	buf[0] = (COMMAND_BIT|REGISTER_CTRL);
	buf[1] = (INTEGRATION_300MS);
	
	ret_val = write(i2c_fd, &buf, 2);
	if(ret_val != 2)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to write() failed. Error in setting integration time for light sensor %d\n\r", errnum);
		printf("Call to write() failed. Error in setting integration time for light sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to write() to set integration time successful. Integration time set to 300ms \n\r");
	}
	
	usleep(500000); //wait for atleast 500ms
	if(errno)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to usleep() failed %d\n\r", errnum);
		printf("Call to usleep() failed %d\n\r", errnum);
	}
	
	/******************************************
	*
	* Read data 
	*
	******************************************/
	
	buf[0] = (COMMAND_BIT|REG_CHAN0_LOW);
	buf[1] = 0x00;
	
	ret_val = write(i2c_fd, buf, 1);
	if(ret_val != 1)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to write() failed. Error in sending command REG_CHAN0_LOW to light sensor %d\n\r", errnum);
		printf("Call to write() failed. Error in sending command REG_CHAN0_LOW to light sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to write() to send command REG_CHAN0_LOW successful.\n\r");
	}
	
	buf[0] = 0x00;
	
	ret_val = read(i2c_fd, buf, 2);
	if(ret_val != 2)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to read() failed. Error in reading from REG_CHAN0_LOW light sensor %d\n\r", errnum);
		printf("Call to read() failed. Error in reading from REG_CHAN0_LOW temp sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to read() for REG_CHAN0_LOW successful.\n\r");
	}
	
	int x = (buf[1] << 8);
	x |= buf[0];
	
	buf[0] = (COMMAND_BIT|REG_CHAN1_LOW);
	buf[1] = 0x00;
	
	ret_val = write(i2c_fd, buf, 1);
	if(ret_val != 1)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to write() failed. Error in sending command REG_CHAN1_LOW to light sensor %d\n\r", errnum);
		printf("Call to write() failed. Error in sending command REG_CHAN1_LOW to light sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to write() to send command REG_CHAN1_LOW successful.\n\r");
	}
	
	buf[0] = 0x00;
	
	ret_val = read(i2c_fd, buf, 2);
	if(ret_val != 2)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to read() failed. Error in reading from REG_CHAN1_LOW light sensor %d\n\r", errnum);
		printf("Call to read() failed. Error in reading from REG_CHAN1_LOW temp sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to read() for REG_CHAN1_LOW successful.\n\r");
	}
	
	x = x << 16;
	x = (buf[1] << 8);
	x |= buf[0];
	
	sensor_data.ir_light_data = x >>16;
	sensor_data.full_light_data = x&0xFFFF;
	sensor_data.visible_light_data = ((sensor_data.full_light_data) - (sensor_data.ir_light_data));
	
	printf("IR: %d\n\r", sensor_data.ir_light_data);
	printf("Full: %d\n\r", sensor_data.full_light_data);
	printf("Visible: %d\n\r", sensor_data.visible_light_data);
	
	close(i2c_fd);
}


/***********************************************************************************************
* Name          : temp_readings
* Description   : Reads the temperature from Si7021
* Parameters    : void
* RETURN        : void
***********************************************************************************************/

void temp_readings(void)
{
	int errnum;
	int ret_val =0;
	int i2c_fd;
	char *i2c_filename = "/dev/i2c-1"; 
	
	i2c_fd = open(i2c_filename, O_RDWR);
	if(i2c_fd <0)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to open() failed. Error in accessing /dev/i2c-1 %d\n\r", errnum);
		printf("Call to open() failed. Error in accessing /dev/i2c-1 %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to open() successful.\n\r");
	}
	
	int sensor_addr = 0x40;
	
	ret_val = ioctl(i2c_fd, I2C_SLAVE, sensor_addr);
	if(ret_val <0)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to ioctl() failed. Error in setting sensor address %d\n\r", errnum);
		printf("Call to ioctl() failed. Error in setting sensor address %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to ioctl() successful.\n\r");
	}
	
	int reg = 0xF3;
	
	ret_val = write(i2c_fd, &reg, 1);
	if(ret_val != 1)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to write() failed. Error in writing to temp sensor %d\n\r", errnum);
		printf("Call to write() failed. Error in writing to temp sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to write() successful.\n\r");
	}
	
	usleep(11000); //wait for atleast 10.8ms
	if(errno)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to usleep() failed %d\n\r", errnum);
		printf("Call to usleep() failed %d\n\r", errnum);
	}
	
	int  n = 2;
	char buf[n];
	
	ret_val = read(i2c_fd, buf, n);
	if(ret_val != n)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to read() failed. Error in reading from temp sensor %d\n\r", errnum);
		printf("Call to read() failed. Error in reading from temp sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to read() successful.\n\r");
	}
	
	int temp = buf[0];
	temp = temp<<8;
	temp |= buf[1];
	
	sensor_data.temp_celcius_data = ((175.72*temp)/65536) - 46.85;
	syslog(LOG_DEBUG, "Temperature in celcius: %f", (float)sensor_data.temp_celcius_data);
	printf("Temperature in celcius: %f\n\r", (float)sensor_data.temp_celcius_data);
	
	close(i2c_fd);
}

/***********************************************************************************************
* Name          : RH_readings
* Description   : Reads the Relative Humidity from Si7021
* Parameters    : void
* RETURN        : void
***********************************************************************************************/

void RH_readings(void)
{
	int errnum;
	int ret_val =0;
	int i2c_fd;
	char *i2c_filename = "/dev/i2c-1"; 
	
	i2c_fd = open(i2c_filename, O_RDWR);
	if(i2c_fd <0)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to open() failed. Error in accessing /dev/i2c-1 %d\n\r", errnum);
		printf("Call to open() failed. Error in accessing /dev/i2c-1 %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to open() successful.\n\r");
	}
	
	int sensor_addr = 0x40;
	
	ret_val = ioctl(i2c_fd, I2C_SLAVE, sensor_addr);
	if(ret_val <0)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to ioctl() failed. Error in setting sensor address %d\n\r", errnum);
		printf("Call to ioctl() failed. Error in setting sensor address %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to ioctl() successful.\n\r");
	}
	
	int reg = 0xE5;
	
	ret_val = write(i2c_fd, &reg, 1);
	if(ret_val != 1)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to write() failed. Error in writing to temp sensor %d\n\r", errnum);
		printf("Call to write() failed. Error in writing to temp sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to write() successful.\n\r");
	}
	
	usleep(11000); //wait for atleast 10.8ms
	if(errno)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to usleep() failed %d\n\r", errnum);
		printf("Call to usleep() failed %d\n\r", errnum);
	}
	
	int  n = 2;
	char buf[n];
	
	ret_val = read(i2c_fd, buf, n);
	if(ret_val != n)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to read() failed. Error in reading from temp sensor %d\n\r", errnum);
		printf("Call to read() failed. Error in reading from temp sensor %d\n\r", errnum);
		return;
	}
	else
	{
		printf("Call to read() successful.\n\r");
	}
	
	int relative_humidity_raw = buf[0];
	relative_humidity_raw = relative_humidity_raw<<8;
	relative_humidity_raw |= buf[1];
	
	sensor_data.rel_humidity_data = ((125*relative_humidity_raw)/65536) - 6;
	syslog(LOG_DEBUG, "Relative Humidity: %f", (float)sensor_data.rel_humidity_data);
	printf("Relative Humidity: %f\n\r", (float)sensor_data.rel_humidity_data);
	
	close(i2c_fd);
}
        
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
   int length1 = 0;
   int length2 = 0;
   int length3 = 0;
   int length4 = 0;
   int length5 = 0;
   int total_length = 0;
   char *str1 = "T:";
   char *str2 = ",H:";
   char *str3 = ",IR:";
   char *str4 = ",FULL:";
   char *str5 = ",VIS:";
   char *str6 = "#";
   
   
   /* Packet format: T:<temp_data>,H:<RH_data>,IR:<IR_data>,FULL:<Full_Light_data>,VIS:<VIsible_Light_data> */
   
   printf("Enter while()\n");
    //5. Call to function for server- client communication
    while(1)
    {
    	temp_readings();
    	
    	length1 = snprintf(NULL, 0, "%0.2f", sensor_data.temp_celcius_data);
    	char *str_temp = malloc(length1+1);
    	snprintf(str_temp, length1+1, "%0.2f", sensor_data.temp_celcius_data);
    	
    	RH_readings();
    	
    	length2 = snprintf(NULL, 0, "%0.2f", sensor_data.rel_humidity_data);
    	char *str_rh = malloc(length2+1);
    	snprintf(str_rh, length2+1, "%0.2f", sensor_data.rel_humidity_data);
    	
    	light_readings();
    	
    	length3 = snprintf(NULL, 0, "%d", sensor_data.ir_light_data);
    	char *str_ir = malloc(length3+1);
    	snprintf(str_ir, length3+1, "%d", sensor_data.ir_light_data);
    	
    	length4 = snprintf(NULL, 0, "%d", sensor_data.full_light_data);
    	char *str_full = malloc(length4+1);
    	snprintf(str_full, length4+1, "%d", sensor_data.full_light_data);
    	
    	length5 = snprintf(NULL, 0, "%d", sensor_data.visible_light_data);
    	char *str_vis = malloc(length5+1);
    	snprintf(str_vis, length5+1, "%d", sensor_data.visible_light_data);
    	
    	total_length = (length1 + length2 + length3 + length4 + length5 +strlen(str1) +strlen(str2) + strlen(str3) +strlen(str4) + strlen(str5) + strlen(str6) -6);
    	char *str_pkt = malloc(total_length);
    	
    	memset(str_pkt, 0, total_length);
    	
    	strcat(str_pkt, str1);
    	strcat(str_pkt, str_temp);
    	strcat(str_pkt, str2);
    	strcat(str_pkt, str_rh);
    	strcat(str_pkt, str3);
    	strcat(str_pkt, str_ir);
    	strcat(str_pkt, str4);
    	strcat(str_pkt, str_full);
    	strcat(str_pkt, str5);
    	strcat(str_pkt, str_vis);  	
    	strcat(str_pkt, str6); 

    	printf("Sending data: %s\n", str_pkt);
    	rt = write(connfd, str_pkt, strlen(str_pkt)); // send the message to client
    	if(rt < 0)
    	{
            perror("Server_Error:");
        }
        else if(rt != strlen(str_pkt))
        {
            printf("partial sent bytes:%d\r\n",rt);
        }

        printf("sent bytes:%d\r\n",rt);
        free(str_temp);
        free(str_rh);
        free(str_ir);
        free(str_full);
        free(str_vis);
        free(str_pkt);
        
    	sleep(2);

    }
    
    //6. Close the socket
    close(sockfd);
    

}
