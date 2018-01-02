#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "common.h"

int
main(int argc, char *const argv[])
{
	int sem_id = -1;
	int ret = -1;
	struct semid_ds sem_buf = {};

	union sem_un{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	} arg;

	sem_id = semget(MY_SEM_ID, 1, 0);
	if (sem_id  >= 0) {
		arg.buf	 = &sem_buf;

		ret = semctl(sem_id, 0, IPC_STAT, arg);

		if (ret != -1) {
			if (sem_buf.sem_otime) {
				printf("Last semop time %s\n", ctime(&sem_buf.sem_otime));
			}

			printf("Last change time %s\n", ctime(&sem_buf.sem_ctime));

			printf("Number of semaphores %ld\n", sem_buf.sem_nsems);

			printf("Owner's user id %d\n", sem_buf.sem_perm.uid);

			printf("Owner's group id %d\n", sem_buf.sem_perm.gid);

			printf("Creator's user id %d\n", sem_buf.sem_perm.cuid);

			printf("Creator's group id %d\n", sem_buf.sem_perm.cgid);

			printf("Permissions 0%o\n", sem_buf.sem_perm.mode);
		}
	} else {
		printf("semget failed.[%s]\n", strerror(errno));
	}


	return 0;
}
