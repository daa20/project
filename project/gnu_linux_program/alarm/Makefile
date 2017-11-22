prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/alarm.bin

objs/alarm.bin: objs/src/alarm.o
	$(CC) -o $@ $^ $(LDFLAGS)
	

modules:

objs/src/alarm.o: ./alarm.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm -rf objs/*.bin objs/src/*.o
