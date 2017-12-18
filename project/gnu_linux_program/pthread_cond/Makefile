prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS= -pthread -lpthread

default: binary modules

binary: objs/pthread_cond.bin

objs/pthread_cond.bin: objs/src/pthread_cond.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/pthread_cond.o: ./pthread_cond.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
