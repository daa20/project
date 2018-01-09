#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>

int 
main(int argc, char *const argv[])
{
	char *pathname = NULL;
	long max_buf_size = -1;
	
	max_buf_size = pathconf(".", _PC_PATH_MAX);
	if (max_buf_size == -1) {
		printf("Obtain current directory failed.[%s]\n", strerror(errno));
		return -1;
	}

	pathname = (char *)malloc(max_buf_size * sizeof(char));
	if (pathname == NULL) {
		printf("malloc failed.\n");
		return -1;
	}

	if (getcwd(pathname, (size_t)max_buf_size) == NULL) {
		printf("Get current work directory failed.[%s]\n", strerror(errno));
		goto end;
	}

	printf("Current Work Directory: %s\n", pathname);

end:
	if (pathname != NULL) {
		free(pathname);
	}

	return 0;
}
