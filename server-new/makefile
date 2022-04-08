CROSS_COMPILE=

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS= -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS= -lrt
endif

all: aesdsocket-new
default: aesdsocket-new

aesdsocket-new : aesdsocket-new.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o aesdsocket-new aesdsocket-new.o $(LDFLAGS)

aesdsocket-new.o : aesdsocket-new.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c aesdsocket-new.c $(LDFLAGS)

clean :
	rm -f *.o aesdsocket-new
