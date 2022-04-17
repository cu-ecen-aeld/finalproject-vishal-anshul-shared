CROSS_COMPILE=

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS= -g -Wall -Werror
endif

all: client-test
default: client-test


client-test.o: client-test.c
	$(CC) $(CFLAGS) -c client-test.c

client-test : client-test.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) client-test.o -o client-test

clean :
	rm -f client-test *.o
