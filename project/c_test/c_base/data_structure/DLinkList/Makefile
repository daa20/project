prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/DLinkList.bin

objs/DLinkList.bin: objs/src/DLinkList.o \
	objs/src/main.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/DLinkList.o: ./DLinkList.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

objs/src/main.o: ./main.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
