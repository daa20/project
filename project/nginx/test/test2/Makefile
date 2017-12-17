prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/signal.bin

objs/signal.bin: objs/src/signal.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/signal.o: ./signal.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
