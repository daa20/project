prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/signal_test.bin

objs/signal_test.bin: objs/src/signal_test.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/signal_test.o: ./signal_test.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
