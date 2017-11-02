prefix=
CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g 

LDFLAGS=

default : binary modules 

binary : objs/strout.bin

objs/strout.bin : objs/src/strout.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ \
		$^ $(LDFLAGS)

objs/src/strout.o : ./strout.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ \
		$^ $(LDFLAGS)

modules:


clean:
	rm -rf objs/*.bin objs/src/*.o
