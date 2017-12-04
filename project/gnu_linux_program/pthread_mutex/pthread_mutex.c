#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <assert.h>

#define MAX_THREADS 	(10)

long protect_var = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *
my_thread_func(void *arg) 
{
	int index = 0;
	int ret = 0;
	int *ptr = (int *)arg;
	
	fprintf(stdout, "Thread %d started\n", *ptr);
	
	for (index = 0; index < 1000; index++) {
		ret = pthread_mutex_lock(&mutex);
		
		assert(ret == 0);
		
		protect_var++;

		ret = pthread_mutex_unlock(&mutex);
		assert(ret == 0);

	}
	pthread_exit(NULL);
}


int 
main(int argc, char *argv[])
{
	pthread_t 	my_threads[MAX_THREADS];
	int 		ret = 0;
	int 		index = 0;

	for (index = 0; index < MAX_THREADS; index++) {
		ret = pthread_create(&my_threads[index], NULL,
				my_thread_func, &index);
		if (ret != 0) {
			fprintf(stderr, "Create pthread[%d] failed![%s]\n", 
					index, strerror(errno));
			exit(-1);
		}
	}

	for (index = 0; index < MAX_THREADS; index++) {
		ret = pthread_join(my_threads[index], NULL);
		if (ret != 0) {
			fprintf(stderr, "Thread[%d] join failed![%s]\n",
					index, strerror(errno));
			exit(-1);
		}
	}
	
	fprintf(stdout, "The protected variable value is %ld\n", protect_var);
	
	ret = pthread_mutex_destroy(&mutex);
	if (ret != 0) {
		fprintf(stderr, "Can't destroy the mutex!\n");
		exit(-1);
	}

	return 0;
}
