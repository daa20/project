/*
 * Test dynamic ld lib.
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "randapi.h"


#define ITERATIONS 100


int
main(int argc, char *argv[])
{
	int i = 0;
	int isum = 0;
	float fsum = 0.0;

	void *handle;
	void *err;

	void (*init_rand_d)(void);
	int (*get_rand_d)(int);
	float (*get_srand_d)(void);


	/* Open a handle to the dynamic library. */
	handle = dlopen("/usr/local/lib/libmyrand.so", RTLD_LAZY);
	if(handle == (void *)0) {
		fputs(dlerror(), stderr);
		exit(-1);
	}


	/* Check access to the init_rand() function. */
	init_rand_d = dlsym(handle, "init_rand");
	err = dlerror();
	if (err != NULL) {
		fputs(err, stderr);
		exit(-1);
	}

	/* Check access to the get_rand() function.*/
	get_rand_d = dlsym(handle, "get_rand");
	err = dlerror();
	if (err != NULL) {
		fputs(err, stderr);
		exit(-1);
	}

	/* Check access to the get_srand() function. */
	get_srand_d = dlsym(handle, "get_srand");
	err = dlerror();
	if (err != NULL) {
		fputs(err, stderr);
		exit(-1);
	}

	/* Initialize the random number API. */
	//init_rand();
	(*init_rand_d)();


	isum = 0;
	for(i = 0; i < ITERATIONS; i++) {
		//isum = isum + get_rand(10);
		isum = isum + (*get_rand_d)(10);
	}

	printf("get_rand(10) avg: %d\n", (int) (isum / ITERATIONS));


	fsum = 0.0;
	for(i = 0; i < ITERATIONS; i++) {
		//fsum = fsum + get_srand();
		fsum = fsum + (*get_srand_d)();
	}

	printf("get_srand() avg: %f\n", (float) (fsum / (float)ITERATIONS));

	dlclose(handle);

	return 0;
}
