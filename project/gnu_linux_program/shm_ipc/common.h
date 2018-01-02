#ifndef _COMMON_H_
#define _COMMON_H_

#define MAX_LINE 80
#define MY_SEM_ID 111

typedef struct {
	long 			type;
	float 			fval;
	unsigned int 	uival;
	char 			strval[MAX_LINE + 1];
} my_type_t;

#endif
