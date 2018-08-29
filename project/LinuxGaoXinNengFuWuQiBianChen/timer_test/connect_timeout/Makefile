prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/connect_timeout.bin 

objs/connect_timeout.bin: ./objs/src/connect_timeout.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/connect_timeout.o: ./connect_timeout.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
