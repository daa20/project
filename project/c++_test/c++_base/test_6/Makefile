prefix=

CC=$(prefix)g++

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/test.bin

objs/test.bin: objs/src/operator.o \
	objs/src/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/operator.o: ./operator.cpp
	$(CC) -c $(INCLUDE) $(CFLAGS) -o $@ $^

objs/src/main.o: ./main.cpp
	$(CC) -c $(INCLUDE) $(CFLAGS) -o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
