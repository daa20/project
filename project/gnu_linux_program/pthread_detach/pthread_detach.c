#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

void *
my_thread_func(void *arg)
{
	int ret = 0;

	fprintf(stdout, "pthread detach: %x\n", (int)pthread_self());
	ret = pthread_detach(pthread_self());
	if (ret != 0) {
		fprintf(stderr, "pthread detach failed![%s]\n", strerror(errno));
	}
	
	fprintf(stdout, "func: %s\n", (char *)arg);

	return (char *)strlen(arg);
}


int 
main(int argc, char *argv[])
{
	pthread_t 	my_thread;
	int 		ret = 0;
	void 		*res = NULL;

	ret = pthread_create(&my_thread, NULL, my_thread_func, "hello world");
	if (ret != 0) {
		fprintf(stderr, "pthread create failed![%s]\n", strerror(errno));
		exit(-1);
	}

	ret = pthread_join(my_thread, &res);
	if (ret != 0) {
		fprintf(stderr, "pthread join failed![%s]\n", strerror(errno));
		exit(-1);
	}

	return 0;
}
