#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>


#define MAX_CONSUMERS 10

pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t condition = PTHREAD_COND_INITIALIZER;


int work_count = 0;


void * producer_thread(void *arg);
void * consumer_thread(void *arg);
int 
main(int argc, char *const argv[])
{
	pthread_t 	consumers[MAX_CONSUMERS];
	pthread_t	producer;
	int 		i = 0;
	
	for (i = 0; i < MAX_CONSUMERS; i++) {

		pthread_create(&consumers[i], NULL, 
				consumer_thread, NULL);
	}

	pthread_create(&producer, NULL,
			producer_thread, NULL);

	pthread_join(producer, NULL);

	while ((work_count > 0));

	for (i = 0; i < MAX_CONSUMERS; i++) {
		pthread_cancel(consumers[i]);
	}
		
	pthread_mutex_destroy(&cond_mutex);
	pthread_cond_destroy(&condition);

	fprintf(stdout, "OK!\n");
	return 0;
}

void *
producer_thread(void *arg)
{
	int 		i = 0;
	int 		j = 0;
	int 		ret = 0;
	double 		result = 0.0;

	fprintf(stdout, "Producer started\n");

	for (i = 0; i < 30; i++) {
		ret = pthread_mutex_lock(&cond_mutex);
		if (ret == 0) {
			fprintf(stdout, "Producer Creating work (%d)\n", work_count);
			
			work_count++;
			pthread_cond_broadcast(&condition);

			assert(pthread_mutex_unlock(&cond_mutex) == 0);
		} else {
			assert(0);
		}
		for (j = 0; j < 6000; j++) {
			result = result + (double)random();
		}
	}
	fprintf(stdout, "Producer finished\n");
	pthread_exit(NULL);

}


void *
consumer_thread(void *arg)
{
	int ret = 0;

	pthread_detach(pthread_self());

	fprintf(stdout, "Consumer %x: Starting.\n", (int)pthread_self());

	/*while (1)*/ {
		assert(pthread_mutex_lock(&cond_mutex) == 0);

		assert((ret = pthread_cond_wait(&condition, &cond_mutex)) == 0);
#if 0
		if (ret == 0) {
			fprintf(stderr, "Consumer %x: error.\n", (int)pthread_self());
		}
#endif
		if (work_count) {
			work_count--;
			fprintf(stdout, "Consumer %x: performed work (%d).\n",
					(int)pthread_self(), work_count);

		}

		assert(pthread_mutex_unlock(&cond_mutex) == 0);
	}

	fprintf(stdout, "Consumer %x: Finished\n", (int)pthread_self());

	pthread_exit(NULL);
}
