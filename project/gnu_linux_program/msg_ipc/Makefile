prefix=

CC= $(prefix)gcc

INCLUDE= -I. #./common.h

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/msg_create.bin  \
		objs/msg_control.bin \
		objs/msg_send.bin    \
		objs/msg_receive.bin \
		objs/msg_delete.bin

objs/msg_create.bin: objs/src/msg_create.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/msg_control.bin: objs/src/msg_control.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/msg_send.bin: objs/src/msg_send.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/msg_receive.bin: objs/src/msg_receive.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/msg_delete.bin: objs/src/msg_delete.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/msg_create.o: ./msg_create.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/msg_control.o: ./msg_control.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/msg_send.o: ./msg_send.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/msg_receive.o: ./msg_receive.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/msg_delete.o: ./msg_delete.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean: 
	rm -rf objs/*.bin objs/src/*.o
