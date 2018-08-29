prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -O3

LDFLAGS=

defaule: binary modules

binary: objs/epoll_test.bin

objs/epoll_test.bin: objs/src/epoll_test.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/epoll_test.o: ./epoll_test.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean: 
	rm -rf objs/*.bin objs/src/*.o
