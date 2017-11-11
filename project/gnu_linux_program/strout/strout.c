/*
 *	string from termial input to file.
 *
 *	date: 2017-11-02
 *
 * */

#include <stdio.h>

#define STR_LEN 80

int 
main(int argc, char *argv[])
{
	char line[STR_LEN + 1] = {};

	FILE *fout = NULL;
	FILE *fin = NULL;

	fout = fopen("testfile.txt", "w");
	if (fout == (FILE *)NULL) {
		return -1;
	}

	fin = fdopen(0, "r");

	while(fgets(line, STR_LEN, fin) != NULL) {
		fputs(line, fout);
	}
	
	fclose(fin);
	fclose(fout);
	return 0;
}
