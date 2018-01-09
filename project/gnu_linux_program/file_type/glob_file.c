#include <stdio.h>
#include <glob.h>


int
main(int argc, char *const argv[])
{
	glob_t 	globbuf;
	int 	err = -1;
	int 	i = 0;

	err = glob("*.[co]", 0, NULL, &globbuf);
	if (err == 0) {
		for (i = 0; i < globbuf.gl_pathc; i++) {
			printf("%s\n", globbuf.gl_pathv[i]);
		}

		globfree(&globbuf);
	}

	return 0;
}
