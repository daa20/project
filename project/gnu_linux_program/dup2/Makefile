prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/dup2.bin

objs/dup2.bin: objs/src/dup2.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/src/dup2.o: ./dup2.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^ 

modules:

clean:
	rm -rf objs/*.bin objs/src/*.o
