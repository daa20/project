prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/cgi.bin

objs/cgi.bin: objs/src/cgi.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/cgi.o: ./cgi.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
