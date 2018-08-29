prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/select.bin
	
objs/select.bin: objs/src/select.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/select.o: ./select.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean: 
	rm -rf objs/*.bin objs/src/*.o
