#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>


int 
main(int argc, char *const argv[])
{
	struct stat stat_buf;

	/* Check to see if a filename was provided. */
	if (argc < 2) {
		printf("Specify a filename to test.\n");
		return -1;
	}

	/* Obtain stat information on the file. */
	if (stat(argv[1], &stat_buf) == -1) {
		printf("Can't stat file[%s].\n", strerror(errno));
		return -1;
	}

	printf("file: %s  ", argv[1]);

	/* Determine the file type from the st_mode. */
	if (S_ISDIR(stat_buf.st_mode)) {
		printf("is a directory.\n");
	} else if (S_ISCHR(stat_buf.st_mode)) {
		printf("is a character special file.\n");
	} else if (S_ISBLK(stat_buf.st_mode)) {
		printf("is a block special file.\n");
	} else if (S_ISREG(stat_buf.st_mode)) {
		printf("is a regular file.\n");
	} else if (S_ISFIFO(stat_buf.st_mode)) {
		printf("is a FIFO special file.\n");
	} else if (S_ISSOCK(stat_buf.st_mode)) {
		printf("is a socket file.\n");
	} else {
		printf("is unknown file.\n");
	}

	return 0;
}
