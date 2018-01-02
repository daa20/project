#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "common.h"


int 
main(int argc, char *const argv[])
{
	int sem_id = -1;
	
	sem_id = semget(MY_SEM_ID, 1, 0666 | IPC_CREAT);

	if (sem_id >= 0) {
		fprintf(stdout, "Sem a create: create a semaphore %d\n", sem_id);
	}

	return 0;
}
