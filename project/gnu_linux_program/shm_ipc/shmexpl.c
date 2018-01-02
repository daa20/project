#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


//#include "common.h"


#define MY_SHM_ID 100
#define MY_SEM_ID 111

#define MAX_STRING 5000

typedef struct {
	int sem_id;
	int counter;
	char string[MAX_STRING + 1];
} MY_BLOCK_T;


int 
main(int argc, char *const argv[])
{
	int 			shm_id = -1;
	int 			ret = -1;
	int 			i = 0;
	MY_BLOCK_T 		*block = NULL;
	struct sembuf 	sb;

	char user;

	if (argc >= 2) {
		if (strncmp(argv[1], "create", strlen("create")) == 0) {
			
			printf("create the shared memory segment and semaphore.\n");
			
			shm_id = shmget(MY_SHM_ID, sizeof(MY_BLOCK_T), (IPC_CREAT | 0666));
			if (shm_id == -1) {
				printf("create shm_id failed.[%s]\n ", strerror(errno));
			}
			
			/* Attach to the segment. */
			block = (MY_BLOCK_T *)shmat(shm_id, (const void *)0, 0);
			
			/* Initialize our semaphore. */
			block->counter = 0;

			/* Create the semaphore. */
			block->sem_id = semget(MY_SEM_ID, 1, (IPC_CREAT | 0666));

			/* Increment the semaphore. */
			sb.sem_num = 0;
			sb.sem_op = 1;
			sb.sem_flg = 0;
			semop(block->sem_id, &sb, 1);

			/* Now, detach from the segment. */
			shmdt((void *)block);


		} else if (strncmp(argv[1], "use", strlen("use")) == 0) {
			/* Use the segment. */

			/* Must specify also a letter (to write to the buffer). */
			user = (char)argv[2][0];

			/* Grab the shared memory segment. */
			shm_id = shmget(MY_SHM_ID, 0, 0);

			/* Attach to it. */
			block = (MY_BLOCK_T *)shmat(shm_id, (const void *)0, 0);

			for (i = 0; i < 2500; i++) {
				/* Give up the CPU temporarily. */
				sleep(0);

				/* Grab the semaphore. */
				sb.sem_num = 0;
				sb.sem_op = -1;
				sb.sem_flg = 0;

				if ( semop(block->sem_id, &sb, 1) != -1) {
					
					block->string[block->counter++] = user;

					/* Release the semaphore. */
					sb.sem_num = 0;
					sb.sem_op = 1;
					sb.sem_flg = 0;
					
					if (semop(block->sem_id, &sb, 1) == -1) {
						printf("Failed to release the semaphore.\n");
					}
				} else {
					printf("Failed to acquire the semaphore.\n");
				}
			}
			
			/* we're done, unmap the shared memory segment. */
			ret = shmdt((void *)block);

		} else if (strncmp(argv[1], "read", strlen("read")) == 0) {
			
			/* Here, we'll read the buffer in the shared segment. */
			shm_id  = shmget(MY_SHM_ID, 0, 0);
			if (shm_id == -1) {
				block = (MY_BLOCK_T *)shmat(shm_id, (const void *)0, 0);

				/* Terminate the buffer. */
				block->string[block->counter + 1]  = 0;

				printf("%s\n", block->string);

				printf("length: %d\n", block->counter);

				ret = shmdt((void *)block);

			} else {
				printf("Unable to read segment.\n");
			}

		} else if (strncmp(argv[1], "remove", strlen("remove")) == 0) { 
			shm_id  = shmget(MY_SHM_ID, 0, 0);
			if (shm_id != -1) {
				block = (MY_BLOCK_T *)shmat(shm_id, (const void *)0, 0);

				/* Remove the semaphore. */
				ret = semctl(block->sem_id, 0, IPC_RMID);

				/* Remove the shared segment. */
				ret = shmctl(shm_id, IPC_RMID, 0);

				if (ret == 0) {
					printf(" Successfully removed the segment.\n");
				}
			}
		} else {

			printf("Unknown command %s\n", argv[1]);
		
		}


	} else {

		printf("Input parameter error, please check it!\n");

	}
	return 0;
}
