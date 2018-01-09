prefix=

CC= $(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/time.bin

objs/time.bin: objs/src/time.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/time.o: ./time.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o

