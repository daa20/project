prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/posixsig.bin
	
objs/posixsig.bin: objs/src/posixsig.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/posixsig.o: ./posixsig.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^
clean:
	rm objs/*.bin objs/src/*.o
