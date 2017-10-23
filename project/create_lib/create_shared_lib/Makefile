all:
	gcc -fPIC -c -Wall initapi.c
	gcc -fPIC -c -Wall randapi.c
	gcc -shared initapi.o randapi.o -o libmyrand.so
	gcc test.c -L. -lmyrand -o test
	export LD_LIBRARY_PATH=./
	ldd ./test




clean:
	rm -rf *.o *.so test
