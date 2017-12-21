#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#include "common.h"

int 
main(int argc, char *const argv[])
{
	int msg_id;

	msg_id = msgget(MY_MQ_ID, 0666 | IPC_CREAT);

	if (msg_id >= 0) {

		fprintf(stdout, "Create a Message Queue %d\n", msg_id);
	} else {
		fprintf(stderr, "Create a Message Queue failed![%s]\n", strerror(errno));
	}

	return 0;
}
