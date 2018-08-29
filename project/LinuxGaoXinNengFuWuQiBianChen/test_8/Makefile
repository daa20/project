prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/epoll.bin

objs/epoll.bin: objs/src/epoll.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/epoll.o: ./epoll.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean: 
	rm -rf objs/*.bin objs/src/*.o
