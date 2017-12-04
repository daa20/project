prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS= -pthread

default: binary modules

binary: objs/pthread_mutex.bin

objs/pthread_mutex.bin: objs/src/pthread_mutex.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/pthread_mutex.o: ./pthread_mutex.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^ 

clean:
	rm objs/*.bin objs/src/*.o
