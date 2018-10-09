prefix=

CC=$(prefix)g++

INCLUDE=-I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/test.bin

objs/test.bin: objs/src/test.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/test.o: ./test.cpp
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
