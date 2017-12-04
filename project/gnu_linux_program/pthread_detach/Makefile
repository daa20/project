prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS= -pthread


default: binary modules

binary: objs/pthread_detach.bin

objs/pthread_detach.bin: objs/src/pthread_detach.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/pthread_detach.o: ./pthread_detach.c
	$(CC) -c $(INCLUDE) $(CFLAGS) \
		-o $@ $^ 
clean:
	rm objs/*.bin objs/src/*.o
