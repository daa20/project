prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/smplfork.bin

objs/smplfork.bin: objs/src/smplfork.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/smplfork.o: ./smplfork.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
