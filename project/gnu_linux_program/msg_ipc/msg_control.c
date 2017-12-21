#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#include "common.h"

int
main(int argc, char *const argv[])
{
	int 			msg_id = -1;
	int 			ret = -1;
	struct msqid_ds buf = {};

	msg_id = msgget(MY_MQ_ID, 0);

	if (msg_id >= 0) {
		fprintf(stdout, "Create a Message Queue %d!\n", msg_id);
		
		ret = msgctl(msg_id, IPC_STAT, &buf);

		buf.msg_qbytes = 4096;

		ret = msgctl(msg_id, IPC_SET, &buf);

		if (ret == 0) {
			fprintf(stdout, "Change Queue size!\n");
		} else {
			fprintf(stderr, "Change Queue size failed[%s]!", 
					strerror(errno));
		}

	} else {
		fprintf(stderr, "Create a Message Queue failed[%s]!",
				strerror(errno));
	}
	return 0;
}
