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
	
	fprintf(stdout, "Thread %s!\n", (char *)arg);

	return (void *)strlen(arg);
	//pthread_exit(arg);
}


int 
main(int argc, char *argv[])
{
	int ret = 0;
	pthread_t my_thread;
	void *res = NULL;

	ret = pthread_create(&my_thread, NULL, my_thread_func, "Hello world");

	if (ret != 0) {
		fprintf(stderr, "Create thread failed![%s]", strerror(errno));
		exit(-1);
	}
	
	ret = pthread_join(my_thread, &res);
	if (ret != 0) {
		fprintf(stdout, "pthread_join failed![%s]\n", strerror(errno));
		exit(-1);
	}

	return 0;
}
