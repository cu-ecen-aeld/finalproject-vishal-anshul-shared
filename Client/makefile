# Author: Anshul Somani
# Makefile to crosscompile the executable for client.c
	

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc	
endif
ifeq ($(CFLAGS),)
	CFLAGS=-Werror -Wall -g  	
endif
ifeq ($(LDFLAGS),)
	LDFLAGS=-pthread	
endif


all: client

default: client

client: client.c
	$(CC) $(CFLAGS) client.c -o client $(LDFLAGS) 
	
.PHONY: clean	

clean: 
	 rm -f client client.o 
	


