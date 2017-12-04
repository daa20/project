#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>


void *
my_thread_func(void *arg)
{
	pthread_t pt;

	fprintf(stdout, "Create Thread successfully!\n");
	
	pt = pthread_self();
	fprintf(stdout, "Thread %x ran!\n", (int)pt);

	pthread_exit(arg);
}


int 
main(int argc, char *argv[])
{
	int ret = 0;
	pthread_t my_thread;

	ret = pthread_create(&my_thread, NULL, my_thread_func, NULL);

	if (ret != 0) {
		fprintf(stderr, "Create thread failed![%s]", strerror(errno));
		exit(-1);
	}

	return 0;
}
