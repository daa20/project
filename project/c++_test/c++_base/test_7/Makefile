prefix=

CC=$(prefix)g++

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/test.bin 

objs/test.bin: objs/src/array.o \
	objs/src/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/array.o: ./array.cpp
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

objs/src/main.o: ./main.cpp
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
