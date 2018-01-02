prefix=

CC= $(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/shmexpl.bin

objs/shmexpl.bin: objs/src/shmexpl.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/shmexpl.o: ./shmexpl.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm objs/*.bin objs/src/*.o
