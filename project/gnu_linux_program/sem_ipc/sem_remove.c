#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "common.h"

int 
main(int argc, char *const argv[])
{
	int sem_id  = -1;
	int ret = -1;

	sem_id = semget(MY_SEM_ID, 1, 0);
	if (sem_id >= 0) {
		ret = semctl(sem_id, 0, IPC_RMID);

		if (ret != -1) {
			printf("Semaphore %d removed.\n", sem_id);
		}
	}
	return 0;
}
