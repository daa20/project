prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/getopt.bin 	\
		objs/getopt_long.bin

objs/getopt.bin: objs/src/getopt.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/getopt_long.bin: objs/src/getopt_long.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/getopt.o: ./getopt.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/getopt_long.o: ./getopt_long.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
