#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#include "common.h"


int 
main(int argc, char *const argv[])
{
	int msg_id = -1;
	int ret = -1;
	my_type_t my_buffer = {};

	msg_id = msgget(MY_MQ_ID, 0);

	if (msg_id >= 0) {
		my_buffer.type = 1L;
		my_buffer.fval = 3.14;
		my_buffer.uival = 512;
		strncpy(my_buffer.strval, "This is a test.\n", MAX_LINE);

		ret = msgsnd(msg_id, (struct msgbuf *)&my_buffer, sizeof(my_type_t), 0);
		if (ret != -1) {
			fprintf(stdout, "Message successfully sent to queue %d\n", msg_id);
		} else {
			fprintf(stderr, "Message sent failed[%s].\n", strerror(errno));
		}

	} else {
		fprintf(stderr, "Create Message Queue failed[%s].\n", strerror(errno));
	}

	return 0;
}
