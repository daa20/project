prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/daysrv.bin objs/daycli.bin

objs/daysrv.bin: objs/src/daysrv.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/daycli.bin: objs/src/daycli.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/daysrv.o: ./daysrv.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^ 

objs/src/daycli.o: ./daycli.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^


clean:
	rm -rf objs/*.bin objs/src/*.o
