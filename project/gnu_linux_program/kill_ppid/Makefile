prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/kill_ppid.bin

objs/kill_ppid.bin: objs/src/kill_ppid.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/kill_ppid.o: ./kill_ppid.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
