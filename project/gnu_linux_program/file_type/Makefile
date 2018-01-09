prefix=

CC=$(prefix)gcc

INCLUDE=

CFLAGS= -Wall -g

LDFLAGS=

default: binary modules

binary: objs/file_type1.bin 	\
		objs/file_type2.bin 	\
		objs/current_dir.bin 	\
		objs/dir_list1.bin		\
		objs/ftw_dir.bin 		\
		objs/glob_file.bin     	\
		objs/inotify_file.bin 	\
		objs/remove_file.bin

objs/file_type1.bin: objs/src/file_type1.o
	$(CC) -o $@ $^ $(LDFLAGS)


objs/file_type2.bin: objs/src/file_type2.o
	$(CC) -o $@ $^ $(LDFLAGS)


objs/current_dir.bin: objs/src/current_dir.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/dir_list1.bin: objs/src/dir_list1.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/ftw_dir.bin: objs/src/ftw_dir.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/glob_file.bin: objs/src/glob_file.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/inotify_file.bin: objs/src/inotify_file.o
	$(CC) -o $@ $^ $(LDFLAGS)

objs/remove_file.bin: objs/src/remove_file.o
	$(CC) -o $@ $^ $(LDFLAGS)

modules:

objs/src/file_type1.o: ./file_type1.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^ 

objs/src/file_type2.o: ./file_type2.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/current_dir.o: ./current_dir.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^ 

objs/src/dir_list1.o: ./dir_list1.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/ftw_dir.o: ./ftw_dir.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/glob_file.o: ./glob_file.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/inotify_file.o: ./inotify_file.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

objs/src/remove_file.o: ./remove_file.c
	$(CC) -c $(CFLAGS) $(INCLUDE) \
		-o $@ $^

clean: 
	rm -rf objs/*.bin objs/src/*.o
