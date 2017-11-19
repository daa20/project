prefix=
CC=$(prefix)gcc

INCLUDE= 

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/process.bin

objs/process.bin: objs/src/process.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/process.o: ./process.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o

