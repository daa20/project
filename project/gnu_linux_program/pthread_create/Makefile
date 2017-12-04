prefix=

CC=$(prefix)gcc

INCLIUDE=

CFLAGS= -Wall -g

LDFLAGS= -pthread

default: binary modules

binary: objs/pthread_create.bin

objs/pthread_create.bin: objs/src/pthread_create.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/pthread_create.o: ./pthread_create.c
	$(CC) -c $(INCLUDE) $(CFLAGS) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
