#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 40
#define FILENAME "input.txt"

typedef struct {
	int id;
	float x_coord;
	float y_coord;
	char name[MAX_LINE + 1];
} MY_TYPE_T;


int 
main(int argc, char *argv[])
{
	MY_TYPE_T object;
	FILE *fin = NULL;

	fin = fopen(FILENAME, "r");
	if (fin == NULL) {
		fprintf(stderr, "cannot open %s\n", FILENAME);
		exit(-1);
	}

	while (!feof(fin)) {
		fscanf(fin, "%d %f %f %s\n",
				&object.id,
				&object.x_coord,
				&object.y_coord,
				object.name);
		printf("%d %f %f %s\n",
				object.id,
				object.x_coord,
				object.y_coord,
				object.name);
	}

	fclose(fin);
	return 0;
}


