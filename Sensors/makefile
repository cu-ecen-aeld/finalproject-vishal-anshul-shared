# Author: Anshul Somani
# Makefile to crosscompile the executable for temp_humidity.c
	

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc	
endif
ifeq ($(CFLAGS),)
	CFLAGS=-Werror -Wall -g  	
endif
ifeq ($(LDFLAGS),)
	LDFLAGS=-pthread	
endif


all: temp_humidity

default: temp_humidity

temp_humidity: temp_humidity.c
	$(CC) $(CFLAGS) temp_humidity.c -o temp_humidity $(LDFLAGS) 
	
.PHONY: clean	

clean: 
	 rm -f temp_humidity temp_humidity.o 
	


