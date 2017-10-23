all:
	gcc -c -Wall initapi.c
	gcc -c -Wall randapi.c
	ar -cru libmyrand.a initapi.o randapi.o
	gcc test.c -L. -lmyrand -o test




clean:
	rm -rf *.o *.a test
