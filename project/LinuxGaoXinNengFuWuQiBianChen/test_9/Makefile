prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS= -lpthread

default: binary modules

binary: objs/epoll_oneshot.bin

objs/epoll_oneshot.bin: objs/src/epoll_oneshot.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/epoll_oneshot.o: ./epoll_oneshot.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean: 
	rm -rf objs/*.bin objs/src/*.o
