# Author: Anshul Somani
# Makefile to crosscompile the executable for distance_sensor.c
	

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc	
endif
ifeq ($(CFLAGS),)
	CFLAGS=-Werror -Wall -g  	
endif
ifeq ($(LDFLAGS),)
	LDFLAGS=-pthread	
endif


all: distance_sensor

default: distance_sensor

distance_sensor: distance_sensor.c
	$(CC) $(CFLAGS) distance_sensor.c -o distance_sensor $(LDFLAGS) 
	
.PHONY: clean	

clean: 
	 rm -f distance_sensor distance_sensor.o 
	


