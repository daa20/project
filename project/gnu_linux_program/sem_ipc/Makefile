prefix=

CC= $(prefix)gcc

INCLUDE= -I.

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/sem_create.bin  		\
		objs/sem_get.bin     		\
		objs/sem_release.bin 		\
		objs/sem_read.bin    		\
		objs/sem_set.bin     		\
		objs/sem_remove.bin  		\
		objs/sem_example1.bin 		\
		objs/sem_example2.bin

objs/sem_create.bin: objs/src/sem_create.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/sem_get.bin: objs/src/sem_get.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/sem_release.bin: objs/src/sem_release.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/sem_read.bin: objs/src/sem_read.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/sem_set.bin: objs/src/sem_set.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/sem_remove.bin: objs/src/sem_remove.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/sem_example1.bin: objs/src/sem_example1.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/sem_example2.bin: objs/src/sem_example2.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules: 

objs/src/sem_create.o:./sem_create.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^ 

objs/src/sem_get.o: ./sem_get.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/sem_release.o: ./sem_release.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/sem_read.o: ./sem_read.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/sem_set.o: ./sem_set.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/sem_remove.o: ./sem_remove.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/sem_example1.o: ./sem_example1.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@  $^ 

objs/src/sem_example2.o: ./sem_example2.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean:
	rm objs/*.bin objs/src/*.o
