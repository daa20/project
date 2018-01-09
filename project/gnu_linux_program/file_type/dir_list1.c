#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>


int
main(int argc, char *const argv[])
{
	DIR 			*dirp;
	struct stat 	statbuf;
	struct dirent 	*dp;

	
	if (argc < 2) {

		printf("Please input any directory.\n");
		return -1;
	}
	
	if (stat(argv[1], &statbuf) == -1) {
		printf("Get %s info failed.[%s]\n", argv[1], strerror(errno));
		return -1;
	}
	
	if (!S_ISDIR(statbuf.st_mode)) {
		printf("input %s is not a directory.\n", argv[1]);
		return -1;
	}

	dirp = opendir(argv[1]);

	while((dp = readdir(dirp)) != NULL) {
#if 1	
		if (stat(dp->d_name, &statbuf) == -1) {
			printf("Get %s info failed.\n", dp->d_name);
			continue;
		}
		
		if (S_ISREG(statbuf.st_mode)) {
			printf("%s is a file.\n", dp->d_name);
			continue;
		}
#endif
		printf("dir: %s\n", dp->d_name);
	}
	closedir(dirp);

	return 0;
}
