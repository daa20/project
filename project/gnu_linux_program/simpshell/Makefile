prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/simpshell.bin

objs/simpshell.bin: objs/src/simpshell.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/simpshell.o: ./simpshell.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^
clean: 
	rm -rf objs/*.bin objs/src/*.o


