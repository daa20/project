prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS=

LDFLAGS=

default: binary modules

binary: objs/strucin.bin

objs/strucin.bin: objs/src/strucin.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/src/strucin.o: $(INCLUDE) \
	./strucin.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ \
		./strucin.c

modules:


clean:
	rm -rf objs/*.bin objs/src/*.o
