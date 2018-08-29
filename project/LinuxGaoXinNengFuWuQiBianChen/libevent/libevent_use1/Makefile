prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS= -levent

default: binary modules

binary: objs/libevent_example.bin

objs/libevent_example.bin: objs/src/libevent_example.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/libevent_example.o: ./libevent_example.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
