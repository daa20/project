prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/input_parameters.bin

objs/input_parameters.bin: objs/src/input_parameters.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/input_parameters.o: ./input_parameters.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
