prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS= 

default: binary modules

binary: objs/send_file.bin

objs/send_file.bin: objs/src/send_file.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/send_file.o: ./send_file.c
	$(CC) -c $(INCLUDE) $(CFLAGS) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
