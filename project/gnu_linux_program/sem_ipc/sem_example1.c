#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>


#define MAX_SEMAPHORES 10

int
main(int argc, char *const argv[])
{
	int 	i = 0;
	int 	ret = -1;
	int 	sem_id  = -1;
	unsigned short sem_array[MAX_SEMAPHORES] = {};
	unsigned short sem_read_array[MAX_SEMAPHORES] = {};

	union sem_um{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	} arg;

	sem_id = semget(IPC_PRIVATE, MAX_SEMAPHORES, IPC_CREAT | 0666);

	if (sem_id >= 0) {
		for(i = 0; i < MAX_SEMAPHORES; i++) {
			sem_array[i] = (unsigned short)(i + 1);
		}

		arg.array = sem_array;

		ret = semctl(sem_id, 0, SETALL, arg);

		if (ret == -1) {
			printf("SETALL failed [%s].\n", strerror(errno));
		}

		arg.array = sem_read_array;

		ret = semctl(sem_id, 0, GETALL, arg);
		if (ret == -1) {
			printf("SETALL failed [%s].\n", strerror(errno));
		}

		for (i = 0; i < MAX_SEMAPHORES; i++) {
			printf("Semaphore %d, value %d\n", i, sem_read_array[i]);
		}

		for (i = 0; i < MAX_SEMAPHORES; i++) {
			ret = semctl(sem_id, i, GETVAL);
			printf("Semaphore %d, value %d\n", i, ret);
		}

		ret = semctl(sem_id, 0, IPC_RMID);

	} else {
		printf("Could not allocate semaphore.[%s]\n", strerror(errno));
	}

	return 0;
}
