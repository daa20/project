#include <stdlib.h>

float
get_srand()
{
	float rand_value = 0.0;
	
	rand_value = (float)rand() / (float)RAND_MAX;

	return rand_value;
}


int
get_rand(int max)
{
	int rand_value = 0;

	rand_value = (int)((float)max * rand() / (RAND_MAX + 1.0));

	return rand_value;
}
