prefix=

CC=$(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -O3

LDFLAGS=

default: binary modules

binary: objs/send_data.bin objs/recv_data.bin

objs/send_data.bin: objs/src/send_data.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/recv_data.bin: objs/src/recv_data.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/send_data.o: ./send_data.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/recv_data.o: ./recv_data.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
