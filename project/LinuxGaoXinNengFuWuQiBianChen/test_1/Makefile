prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -O3 

LDFLAGS=

default: binary modules

binary: objs/byte_order.bin

objs/byte_order.bin: objs/src/byte_order.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/byte_order.o: ./byte_order.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm objs/*.bin objs/src/*.o
