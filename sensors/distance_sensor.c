/*

Author: Anshul Somani
Date: April 5 2022
Description: This code is used to read temperature and humidity values from Si7021 sensor breakout board	
			 from sparkfun. It reads both the values in no master hold mode and when the sensor is connected 
			 to the I2C-1 bus on BeagleBone Black. 
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

#include <string.h>

int main()
{	
	int errnum;
	int ret_val =0;
	int i2c_fd;
	char *i2c_filename = "/dev/i2c-1"; 
	
	i2c_fd = open(i2c_filename, O_RDWR);
	if(i2c_fd <0)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to open() failed. Error in accessing /dev/i2c-1\n\r");
		printf("Call to open() failed. Error in accessing /dev/i2c-1 %d\n\r", errnum);
		return -1;
	}
	else
	{
		printf("Call to open() successful.\n\r");
	}
	
	//TODO: define the address as macros
	int sensor_addr = 0x41;
	//int sensor_addr_write = 0x81;
	
	ret_val = ioctl(i2c_fd, I2C_SLAVE, sensor_addr);
	if(ret_val <0)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to ioctl() failed. Error in setting sensor address\n\r");
		printf("Call to ioctl() failed. Error in setting sensor address %d\n\r", errnum);
		return -1;
	}
	else
	{
		printf("Call to ioctl() successful.\n\r");
	}
	
	char reg[2]; 
	
	/* Start Factory Calibration */
	reg[0] = 0x10;
	reg[1] = 0x0A;
	
	ret_val = write(i2c_fd, &reg, 2);
	if(ret_val != 2)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to write() failed. Error in writing to distance sensor\n\r");
		printf("Call to write() failed. Error in writing to distance sensor. Factory Calibration %d\n\r", errnum);
		return -1;
	}
	else
	{
		printf("Factory Calibration: Call to write() successful.\n\r");
	}
	
	sleep(3); //Sleep for 3s to complete calibration
	if(errno)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to sleep() failed\n\r");
		printf("Call to sleep() failed %d\n\r", errnum);
	}
	
	int  n = 15;
	char buf[n];
	
	memset(&buf[0], 0, 15);
	
	buf[0] = 0x1E;
	buf[1] = 0x00;
	
	//while(buf[1] == 0x00)
	{
		ret_val = write(i2c_fd, &buf[0], 1);
		if(ret_val != 1)
		{
			errnum = errno;
			syslog(LOG_ERR, "Call to write() failed. Error in writing to distance sensor\n\r");
			printf("Call to write() failed. Error in writing to distance sensor. Factory Calibration 0x1E %d\n\r", errnum);
			return -1;
		}
		else
		{
			printf("actory Calibration write to 0x1E. Call to write() successful.\n\r");
		}
		
		ret_val = read(i2c_fd, &buf[1], 1);
		if(ret_val != 1)
		{
			errnum = errno;
			syslog(LOG_ERR, "Call to read() failed. Error in reading from distance sensor\n\r");
			printf("Call to read() failed. Error in reading from distance sensor. Factory Calibration Read from 0x1E %d\n\r", errnum);
			return -1;
		}
		else
		{
			printf("Call to read() successful. Factory Calibration Read from 0x1E data: %d\n\r", buf[1]);
		}
	}
	
	memset(&buf[0], 1, 15);
	
	buf[0] = 0x20;
	
	ret_val = write(i2c_fd, &buf[0], 1);
	if(ret_val != 1)
	{
		errnum = errno;	
		syslog(LOG_ERR, "Call to write() failed. Error in writing to distance sensor\n\r");
		printf("Call to write() failed. Error in writing to distance sensor. Factory Calibration 0x20 %d\n\r", errnum);
		return -1;
	}
	else
	{
		printf("Factory Calibration write to 0x20. Call to write() successful.\n\r");
	}
	ret_val = read(i2c_fd, &buf[1], 14);
	if(ret_val != 14)
	{
		errnum = errno;
		syslog(LOG_ERR, "Call to read() failed. Error in reading from distance sensor\n\r");
		printf("Call to read() failed. Error in reading from distance sensor. Factory Calibration Read from 0x20 %d\n\r", errnum);
		return -1;
	}
	else
	{
		for(int i = 1; i<=14; i++)
		{
			printf("Call to read() successful. Factory Calibration Read from 0x20 data: %d\n\r", buf[i]);
		}
		
	}
	
	memset(&buf[0], 2, 15);
	
	buf[0] = 0x01;
	
	ret_val = write(i2c_fd, &buf[0], 1);
	if(ret_val != 1)
	{
		errnum = errno;	
		syslog(LOG_ERR, "Call to write() failed. Error in writing to distance sensor\n\r");
		printf("Call to write() failed. Error in writing to distance sensor. Major Version of App0 0x01 %d\n\r", errnum);
		return -1;
	}
	else
	{
		printf("Major Version of App0 write to 0x01. Call to write() successful.\n\r");
	}
	ret_val = read(i2c_fd, &buf[1], 1);
	if(ret_val != 1)
	{
		errnum = errno;	
		syslog(LOG_ERR, "Call to read() failed. Error in reading from distance sensor\n\r");
		printf("Call to read() failed. Error in reading from distance sensor. Major Version of App0 Read from 0x01 %d\n\r", errnum);
		return -1;
	}
	else
	{
			printf("Call to read() successful. Major Version of App0 Read from 0x01 data: %d\n\r", buf[1]);	
	}
	
	//TODO: memcmp calibration data
	
	
	memset(&buf[0], 3, 15);
	
	buf[0] = 0x12;
	
	ret_val = write(i2c_fd, &buf[0], 1);
	if(ret_val != 1)
	{
		errnum = errno;	
		syslog(LOG_ERR, "Call to write() failed. Error in writing to distance sensor\n\r");
		printf("Call to write() failed. Error in writing to distance sensor. Minor and patch revision no of App0 0x12 %d\n\r", errnum);
		return -1;
	}
	else
	{
		printf("Minor and patch revision no of App0 write to 0x12. Call to write() successful.\n\r");
	}
	ret_val = read(i2c_fd, &buf[1], 1);
	if(ret_val != 1)
	{
		errnum = errno;	
		syslog(LOG_ERR, "Call to read() failed. Error in reading from distance sensor\n\r");
		printf("Call to read() failed. Error in reading from distance sensor. Minor and patch revision no of App0 Read from 0x12 %d\n\r", errnum);
		return -1;
	}
	else
	{
			printf("Call to read() successful. Minor and patch revision no of App0 Read from 0x12 data: %d\n\r", buf[1]);	
	}
	
	
	/* Start App0 */
	memset(&buf[0], 4, 15);
	buf[0] = 0x08;
	buf[1] = 0x03;
	buf[2] = 0x23;
	buf[3] = 0x00;
	buf[4] = 0x00;
	buf[5] = 0x00;
	buf[6] = 0x64;
	buf[7] = 0xD8;
	buf[8] = 0x04;
	buf[9] = 0x02;
	
	ret_val = write(i2c_fd, &buf[0], 10);
	if(ret_val != 10)
	{
		errnum = errno;	
		syslog(LOG_ERR, "Call to write() failed. Error in writing to distance sensor\n\r");
		printf("Call to write() failed. Error in writing to distance sensor. Started App0 %d\n\r", errnum);
		return -1;
	}
	else
	{
		printf("Started App0. Call to write() successful.\n\r");
	}
	
	memset(&buf[0], 5, 15);
	buf[0] = 0x1D;
	
	ret_val = write(i2c_fd, &buf[0], 1);
	if(ret_val != 1)
	{
		errnum = errno;	
		syslog(LOG_ERR, "Call to write() failed. Error in writing to distance sensor\n\r");
		printf("Call to write() failed. Error in writing to distance sensor. Read data %d\n\r", errnum);
		return -1;
	}
	else
	{
		printf("Read data. Call to write() successful.\n\r");
	}
	ret_val = read(i2c_fd, &buf[1], 10);
	if(ret_val != 10)
	{
		errnum = errno;	
		syslog(LOG_ERR, "Call to read() failed. Error in reading from distance sensor\n\r");
		printf("Call to read() failed. Error in reading from distance sensor. Read data %d\n\r", errnum);
		return -1;
	}
	else
	{
		for(int i = 1; i<=10; i++)
		{
			printf("Call to read() successful. Read data: %d\n\r", buf[i]);	
		}
			
	}
	
	return 0;
	
	
	
}
