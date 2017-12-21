#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

#include "common.h"

int
main(int argc, char *const argv[])
{
	my_type_t my_buffer = {};
	int msg_id = -1;
	int ret = -1;

	msg_id = msgget(MY_MQ_ID, 0);

	if (msg_id >= 0) {
		
		ret = msgrcv(msg_id, (struct msgbuf *)&my_buffer, sizeof(my_type_t), 1L, 0);

		if (ret != 1) {
			
			fprintf(stdout, "Message Type: %ld\n", my_buffer.type);
			fprintf(stdout, "Float Value: %f\n", my_buffer.fval);
			fprintf(stdout, "Uint Value: %d\n", my_buffer.uival);
			fprintf(stdout, "String Value: %s\n", my_buffer.strval);

		} else {
			
			fprintf(stderr, "Message Queue receive failed[%s].\n",
					strerror(errno));
		}
	} else {
		fprintf(stderr, "Message Queue failed[%s].\n", strerror(errno));
	}
	return 0;
}
