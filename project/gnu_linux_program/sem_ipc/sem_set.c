#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "common.h"

int 
main(int argc, char *const argv[])
{
	int sem_id = -1;
	int cnt = 0;

	sem_id = semget(MY_SEM_ID, 1, 0);
	if(sem_id >= 0) {
		/* Read the current semaphore count. */
		cnt = semctl(sem_id, 0, SETVAL, 6);

		if (cnt != -1) {
			printf("semctl: semaphore count update.\n");
		}
	}

	return 0;
}


