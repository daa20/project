#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 	40
#define MAX_OBJECTS 	3
#define FILENAME 	"input.txt"

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

typedef struct {
	int 	id;
	float 	x_coord;
	float 	y_coord;
	char 	name[MAX_LINE + 1];

} MY_TYPE_T;

int
main(int argc, char *argv[])
{
	/* initialize an array fo three objects. */
	MY_TYPE_T objects[MAX_OBJECTS] = {
		{
			0, 1.5, 8.4, "first-object"
		},
		{
			1, 9.2, 7.4, "second-object"
		},
		{
			2, 4.2, 5.6, "final-object"
		}
	};

	int index = 0;
	FILE *fout = NULL;
	int array_size = 0;

	/* open file. */
	fout = fopen(FILENAME, "w");
	if (fout == NULL) {
		exit(-1);
	}

	array_size = ARRAY_SIZE(objects);
	
	/* Emit each of the objects, one per line. */
	for (index = 0; index <  array_size; index++) {
		fprintf(fout, "%d %f %f  %s\n",
				objects[index].id,
				objects[index].x_coord,
				objects[index].y_coord,
				objects[index].name);
	}

	fclose(fout);
	return 0;
}
