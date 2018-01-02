#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "common.h"

int 
main(int argc, char *const argv[])
{
	int sem_id = -1;
	struct sembuf sem_buf = {};

	sem_id =  semget(MY_SEM_ID, 1, 0);

	if (sem_id >= 0) {
		fprintf(stdout, "sem release: Releasing semaphore %d\n",
				sem_id);

		sem_buf.sem_num = 0;
		sem_buf.sem_op = 1;
		sem_buf.sem_flg = 0;

		/* Release the semaphore. */
		if (semop(sem_id, &sem_buf, 1) == -1) {
			fprintf(stderr, "sem release: semop failed\n");
			exit(-1);
		}

		fprintf(stdout, "sem release: semaphore released %d\n", sem_id);
	}

	return 0;
}
