/*

//TODO: Header with author, description, etc

*/

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>

int main()
{	
	//TODO: errnum
	int ret_val =0;
	int i2c_fd;
	char *i2c_filename = "/dev/i2c-1"; //TODO: Cross check this in /dev on BBB
	
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
	//int sensor_addr_write = 0x81;
	
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
	
	int temp_celcius = ((175.72*temp)/65536) - 46.85;
	syslog(LOG_DEBUG, "Temperature in celcius: %d", (int)temp_celcius);
	printf("Temperature in celcius: %d", (int)temp_celcius);
	
	/**************************************************
	*
	*   Humidity
	*
	***************************************************/
	reg = 0xE5;
	
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
	
	int relative_humidity_raw = buf[0];
	relative_humidity_raw = relative_humidity_raw<<8;
	relative_humidity_raw |= buf[1];
	
	int rel_humidity = ((125*relative_humidity_raw)/65536) - 6;
	syslog(LOG_DEBUG, "Relative Humidity: %d", (int)rel_humidity);
	printf("Relative Humidity: %d", (int)rel_humidity);
	
	return 0;
	
	
	
}
