# Author: Anshul Somani
# Makefile to crosscompile the executable for temp_humidity.c, distance_sensor.c and light_sensor.c
	

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc	
endif
ifeq ($(CFLAGS),)
	CFLAGS=-Werror -Wall -g  	
endif
ifeq ($(LDFLAGS),)
	LDFLAGS=-pthread	
endif


all: temp_humidity distance_sensor light_sensor

default: temp_humidity distance_sensor light_sensor

temp_humidity: temp_humidity.c
	$(CC) $(CFLAGS) temp_humidity.c -o temp_humidity $(LDFLAGS) 
	
distance_sensor: distance_sensor.c
	$(CC) $(CFLAGS) distance_sensor.c -o distance_sensor $(LDFLAGS) 

light_sensor: light_sensor.c
	$(CC) $(CFLAGS) light_sensor.c -o light_sensor $(LDFLAGS) 
	
.PHONY: clean	

clean: 
	 rm -f temp_humidity temp_humidity.o distance_sensor distance_sensor.o light_sensor light_sensor.o
	


