#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>


int 
main(int argc, char *const argv[])
{
	struct stat 	stat_buf;
	struct passwd 	*pwd;
	struct group 	*grp;
	struct tm 		*tm;
	char 			tm_str[257];

	/* Check to see if a filename was provided. */
	if (argc < 2) {

		printf("Specify a file to test.\n");
		return -1;
	}

	/* Obtain stat information on the file. */
	if (stat(argv[1], &stat_buf) == -1) {
		printf("Can't stat file.\n");
		return -1;
	}

	printf("file: %s, filesize: %ld.\n", argv[1], stat_buf.st_size);
	
	/* Obtain the user id. */
	pwd = getpwuid(stat_buf.st_uid);
	if (pwd != NULL) {
		printf("File Owner: %s\n", pwd->pw_name);
	}

	/* Obtain the group state. */
	grp = getgrgid(stat_buf.st_gid);
	if (grp != NULL) {
		printf("File Group: %s\n", grp->gr_name);
	}

	tm = localtime(&stat_buf.st_mtime);
	strftime(tm_str, sizeof(tm_str), nl_langinfo(D_T_FMT), tm);
	printf("File Date: %s\n", tm_str);


	return 0;
}
