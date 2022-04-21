/*

Author: Anshul Somani
Date: April 5 2022
Description: This code is used to read luminosity values from Adafruit TSL2591 sensor breakout board.
			 It is connected to the I2C-1 bus on BeagleBone Black. 
			 This code was used to test the I2C interfacing with the sensor for AESD final project Spring 2022

*/

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>

#define TSL2591_GAIN_MED (0x10) // Medium gain (25x)
#define COMMAND_BIT (0xA0)
#define REGISTER_CTRL (0x01)
#define INTEGRATION_300MS (0x02)
#define REG_CHAN0_LOW (0x14)
#define REG_CHAN1_LOW (0x16)

int main()
{	
	int ret_val =0;
	int i2c_fd;
	char *i2c_filename = "/dev/i2c-1"; 
	
	i2c_fd = open(i2c_filename, O_RDWR);
	if(i2c_fd <0)
	{
		syslog(LOG_ERR, "Call to open() failed. Error in accessing /dev/i2c-1 \n\r");
		printf("Call to open() failed. Error in accessing /dev/i2c-1\n\r");
		return -1;
	}
	else
	{
		printf("Call to open() successful.\n\r");
	}
	
	int sensor_addr = 0x29;
	
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
	
	
	/******************************************
	*
	* Set Gain 
	*
	******************************************/
	
	int  n = 2;
	char buf[n];
	
	buf[0] = (COMMAND_BIT|REGISTER_CTRL);
	buf[1] = (TSL2591_GAIN_MED);
	
	ret_val = write(i2c_fd, &buf, 2);
	if(ret_val != 2)
	{
		syslog(LOG_ERR, "Call to write() failed. Error in setting gain for light sensor\n\r");
		printf("Call to write() failed. Error in setting gain for light sensor\n\r");
		return -1;
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
		syslog(LOG_ERR, "Call to write() failed. Error in setting integration time for light sensor\n\r");
		printf("Call to write() failed. Error in setting integration time for light sensor\n\r");
		return -1;
	}
	else
	{
		printf("Call to write() to set integration time successful. Integration time set to 300ms\n\r");
	}
	
	usleep(500); //wait for atleast 500ms
	if(errno)
	{
		syslog(LOG_ERR, "Call to usleep() failed\n\r");
		printf("Call to usleep() failed\n\r");
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
		syslog(LOG_ERR, "Call to write() failed. Error in sending command REG_CHAN0_LOW to light sensor\n\r");
		printf("Call to write() failed. Error in sending command REG_CHAN0_LOW to light sensor\n\r");
		return -1;
	}
	else
	{
		printf("Call to write() to send command REG_CHAN0_LOW successful.\n\r");
	}
	
	buf[0] = 0x00;
	
	ret_val = read(i2c_fd, buf, 2);
	if(ret_val != 2)
	{
		syslog(LOG_ERR, "Call to read() failed. Error in reading from REG_CHAN0_LOW light sensor\n\r");
		printf("Call to read() failed. Error in reading from REG_CHAN0_LOW temp sensor\n\r");
		return -1;
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
		syslog(LOG_ERR, "Call to write() failed. Error in sending command REG_CHAN1_LOW to light sensor\n\r");
		printf("Call to write() failed. Error in sending command REG_CHAN1_LOW to light sensor\n\r");
		return -1;
	}
	else
	{
		printf("Call to write() to send command REG_CHAN1_LOW successful.\n\r");
	}
	
	buf[0] = 0x00;
	
	ret_val = read(i2c_fd, buf, 2);
	if(ret_val != 2)
	{
		syslog(LOG_ERR, "Call to read() failed. Error in reading from REG_CHAN1_LOW light sensor\n\r");
		printf("Call to read() failed. Error in reading from REG_CHAN1_LOW temp sensor\n\r");
		return -1;
	}
	else
	{
		printf("Call to read() for REG_CHAN1_LOW successful.\n\r");
	}
	
	x = x << 16;
	x = (buf[1] << 8);
	x |= buf[0];
	
	int ir = x >>16;
	int full = x&0xFFFF;
	int visible = full -ir;
	
	printf("IR: %d\n\r", ir);
	printf("Full: %d\n\r", full);
	printf("Visible: %d\n\r", visible);
	//TODO: Lux
	
}
