prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules


binary: objs/strucout.bin

objs/strucout.bin : objs/src/strucout.o
	$(CC) -o $@ $^ $(LDFLAGS)

	
objs/src/strucout.o: $(INCLUDE) \
	./strucout.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ ./strucout.c \
		$(LDFLAGS)

modules:

clean:
	rm objs/*.bin objs/src/*.o
