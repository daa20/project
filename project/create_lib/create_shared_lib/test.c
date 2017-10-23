#include "randapi.h"


#define ITERATIONS 100

int
main(int argc, char *argv[])
{
	int i = 0;
	int isum = 0;
	float fsum = 0.0;

	/* Initialize the random number API. */
	init_rand();

	isum = 0;
	for(i = 0; i < ITERATIONS; i++) {
		isum = isum + get_rand(10);
	}

	printf("get_rand(10) avg: %d\n", (int) (isum / ITERATIONS));


	fsum = 0.0;
	for(i = 0; i < ITERATIONS; i++) {
		fsum = fsum + get_srand();
	}

	printf("get_srand() avg: %f\n", (float) (fsum / (float)ITERATIONS));

	return 0;
}
