prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/binin.bin

objs/binin.bin: objs/src/binin.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
objs/src/binin.o: $(INCLUDE) \
	./binin.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ ./binin.c

modules:

clean:
	rm -rf objs/*.bin objs/src/*.o

