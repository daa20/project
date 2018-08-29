prefix=

CC=$(prefix)g++

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/timer_test.bin 

objs/timer_test.bin: objs/src/timer_test.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/timer_test.o: ./timer_test.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean: 
	rm -rf objs/*.bin objs/src/*.o
