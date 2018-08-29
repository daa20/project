prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g 

LDFLAGS=

default: binary modules

binary: objs/socket_create.bin
	
objs/socket_create.bin: objs/src/socket_create.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/socket_create.o: ./socket_create.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean: 
	rm -rf objs/*.bin objs/src/*.o
