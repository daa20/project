#include <stdio.h>
#include <ftw.h>
#include <sys/stat.h>


int fn_check (const char *fpath, const struct stat *sb, int typeflag)
{
	if (typeflag == FTW_F) {
		printf("File %s (size: %d).\n", fpath, (int)sb->st_size);
	} else if (typeflag ==  FTW_D) {
		printf("Directory %s.\n", fpath);
	} else {
		printf("Unknow type!\n");
		return -1;
	}

	return 0;
}

int 
main(int argc, char *const argv[])
{
	if (argc < 2) {
		printf("Please check the input parameter.\n");
		return -1;
	}


	if (ftw(argv[1], fn_check, 1) == -1) {
		printf("ftw error!\n");
		return -1;
	}
	
	return 0;
}
