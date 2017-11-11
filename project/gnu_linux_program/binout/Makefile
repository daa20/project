prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/binout.bin

objs/binout.bin: objs/src/binout.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/src/binout.o: $(INCLUDE) \
	./binout.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ \
		./binout.c 

modules:

clean:
	rm -rf objs/*.bin objs/src/*.o
