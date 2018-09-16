prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/LinkList.bin

objs/LinkList.bin: objs/src/LinkList.o \
	objs/src/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/LinkList.o: ./LinkList.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

objs/src/main.o: ./main.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
