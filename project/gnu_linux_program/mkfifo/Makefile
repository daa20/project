prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS=

LDFLAGS=

default: binary modules

binary: objs/mkfifo_write.bin objs/mkfifo_read.bin

objs/mkfifo_write.bin: objs/src/mkfifo_write.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/mkfifo_read.bin: objs/src/mkfifo_read.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/src/mkfifo_write.o: ./mkfifo_write.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/mkfifo_read.o: ./mkfifo_read.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

modules:

clean:
	rm -rf objs/*.bin objs/src/*.o
