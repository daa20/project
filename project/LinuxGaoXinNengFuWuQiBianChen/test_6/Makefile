prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/test_uid.bin

objs/test_uid.bin: objs/src/test_uid.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/test_uid.o: ./test_uid.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
