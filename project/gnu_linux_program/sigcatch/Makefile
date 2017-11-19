prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/sigcatch.bin

objs/sigcatch.bin: objs/src/sigcatch.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/sigcatch.o: ./sigcatch.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^
clean:
	rm -rf objs/*.bin objs/src/*.o
