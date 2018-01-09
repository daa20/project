#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/inotify.h>

#define MAX_EVENTS 256
#define BUFFER_SIZE (MAX_EVENTS * sizeof(struct inotify_event))

static void
emit_event(struct inotify_event *ievent) 
{
	if (ievent->len) {
		printf("[%s] ", ievent->name);
	}

	if (ievent->mask & IN_ACCESS) {
		printf("Accessed\n");
	}

	if (ievent->mask & IN_MODIFY) {
		printf("Modified\n");
	}
	
	if (ievent->mask & IN_ATTRIB) {
		printf("Attributes changed\n");
	}

	if (ievent->mask & IN_CLOSE_WRITE) {
		printf("Closed (writeable)\n");
	}

	if (ievent->mask & IN_CLOSE_NOWRITE) {
		printf("Closed (unwriteable)\n");
	}

	if (ievent->mask & IN_OPEN) {
		printf("Opened\n");
	}

	if (ievent->mask & IN_MOVED_FROM) {
		printf("File moved from\n");
	}

	if (ievent->mask & IN_MOVED_TO) {
		printf("File moved to\n");
	}

	if (ievent->mask & IN_CREATE) {
		printf("Subfile created\n");
	}

	if (ievent->mask & IN_DELETE) {
		printf("Subfile deleted\n");
	}

	if (ievent->mask & IN_DELETE_SELF) {
		printf("Self deleted\n");
	}

	if (ievent->mask & IN_MOVE_SELF) {
		printf("Self moved\n");
	}


	return;
}

static int
watch(int fd)
{
	char ev_buffer[BUFFER_SIZE];
	struct inotify_event *ievent;
	int len = -1;
	int i = 0;

	while (1) {
		len = read(fd, ev_buffer, BUFFER_SIZE);

		if (len < 0) {
			if (errno == EINTR) continue;
		}

		i = 0;
		while (i < len) {
			ievent = (struct inotify_event *)&ev_buffer[i];
			
			emit_event(ievent);

			i += sizeof(struct inotify_event) + ievent->len;
		}
	}
	return 0;
}


int 
register_watchpoint(int fd, char *dir){

	int err = -1;
	err = inotify_add_watch(fd, dir, IN_ALL_EVENTS);
	return err;
}


int 
main(int argc, char *const argv[])
{
	int ifd = -1;
	int err = -1;

	if (argc < 2) {

		printf("Please check the input parameter.\n");
		return -1;

	}

	ifd = inotify_init();
	if (ifd < 0) {
		printf("Cant't init inotify.[%s]\n", strerror(errno));
		return -1;
	}

	err = register_watchpoint(ifd, argv[1]);
	if (err < 0) {
		printf("Can't add watch.[%s]\n", strerror(errno));
		return -1;
	}

	watch(ifd);

	close(ifd);
	return 0;
}
