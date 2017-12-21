#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#include "common.h"

int
main(int argc, char *const argv[])
{
	int msg_id = -1;
	int ret = -1;

	msg_id = msgget(MY_MQ_ID, 0);

	if (msg_id >= 0) {

		ret = msgctl(msg_id, IPC_RMID, NULL);

		if (ret != -1) {
			
			fprintf(stdout, "Message Queue %d successfully removed.\n", msg_id);

		} else {
			
			fprintf(stderr, "Message Queue remove failed[%s].\n",
					strerror(errno));
		}

	} else {

		fprintf(stderr, "Message Queue failed[%s]\n", strerror(errno));
	
	}
	return 0;
}
