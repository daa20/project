#include <stdio.h>
#include <stdlib.h>

#define PATHNAME "input.txt"
#define MAX_LINE 40
#define MAX_OBJECTS 3
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))


typedef struct {
	int id;
	float x_coord;
	float y_coord;
	char name[MAX_LINE + 1];
} MY_TYPE_T;


int 
main(int argc, char *argv[])
{	
	MY_TYPE_T 	objects[MAX_OBJECTS] = {
					{
						0, 1.2, 2.1, "first_object"
					},
					{
						1, 2.3, 3.2, "second_object"
					},
					{
						2, 5.3, 7.2, "final_object"
					}
				};
	
	int objs_size = ARRAY_SIZE(objects);
	
	FILE *fout = NULL;

	fout = fopen(PATHNAME, "w");
	if (fout == NULL) {
		fprintf(stderr, "cannot open %s\n", PATHNAME);
		exit(-1);
	}

	if (fwrite(objects, sizeof(MY_TYPE_T), objs_size, fout) <= 0) {
		printf("cannot write into %s\n", PATHNAME);
	}
	
	fclose(fout);
	return 0;
}


