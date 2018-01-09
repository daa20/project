#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char *const argv[])
{	
	FILE 	*fp = NULL;
	char 	filename[L_tmpnam + 1] = "fileXXXXXX";
	int 	err = -1;

	err = mkstemp(filename);

	fp = fopen(filename, "w");
	
	if (fp != NULL) {
		
		fclose(fp);
#if 1	
		err = remove(filename);
		if (!err) {
			
			printf("%s removed\n", filename);
		
		}
#endif
	}

	return 0;
}
