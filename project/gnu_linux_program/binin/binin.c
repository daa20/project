#include <stdio.h>
#include <stdlib.h>

#define PATHNAME "input.txt"
#define MAX_LINE 40

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

	fin = fopen(PATHNAME, "r");
	if (fin == NULL) {
		fprintf(stderr, "cannot open %s\n", PATHNAME);
		exit(-1);
	}

	fseek(fin, 2 * sizeof(MY_TYPE_T), SEEK_SET);
	fread(&object, sizeof(MY_TYPE_T), 1, fin);
	printf("%d %f %f %s\n",
			object.id,
			object.x_coord,
			object.y_coord,
			object.name);

	rewind(fin);// move fd to head of file.

	fseek(fin, 1 * sizeof(MY_TYPE_T), SEEK_SET);
	fread(&object, sizeof(MY_TYPE_T), 1, fin);
	printf("%d %f %f %s\n",
			object.id,
			object.x_coord,
			object.y_coord,
			object.name);
	
	rewind(fin); //move fd to head of file.

	fread(&object, sizeof(MY_TYPE_T), 1, fin);
	printf("%d %f %f %s\n", 
			object.id,
			object.x_coord,
			object.y_coord,
			object.name);

	fclose(fin);
	return 0;
}
