#include <stdlib.h>
#include <time.h>

void
init_rand(void)
{
	time_t seed;

	seed = time(NULL);

	srand(seed);

	return;
}
