prefix=
CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default : binary modules

binary : objs/strin.bin

objs/strin.bin : objs/src/strin.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS)

objs/src/strin.o : ./strin.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS)

modules:

clean:
	rm -rf objs/*.bin objs/src/*.o
