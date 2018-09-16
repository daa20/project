prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/CircleList.bin

objs/CircleList.bin: objs/src/CircleList.o \
	objs/src/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/CircleList.o: ./CircleList.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

objs/src/main.o: ./main.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean: 
	rm objs/*.bin objs/src/*.o
