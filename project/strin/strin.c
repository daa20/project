/*
 *	Read file into terminal.
 *	date: 2017-11-02
 *
 * */

#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 80

int
main(int argc, char *argv[])
{
	FILE *fin = NULL;
	
	char line[80 + 1] = {};

	fin = fopen("./testfile.txt", "r");
	if (fin == (FILE *)0) {
		exit(-1);
	}
	
	while(fgets(line, STR_LEN, fin) != NULL) {
		fprintf(stdout, "%s", line);
	}

	fclose(fin);
	return 0;
}
