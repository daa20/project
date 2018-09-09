#include <stdio.h>
#include <stdlib.h>
#include "SeqQueue.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	SeqQueue* queue = SeqQueue_Create(20);
	printf("Capacity : %d\n",SeqQueue_Capacity(queue));
	printf("Length : %d\n",SeqQueue_Length(queue));
	
	int a[20] = {0};
	int i = 0;
	for(i=0;i<10;i++)
	{
		a[i] = i + 1;
		SeqQueue_Append(queue,a+i);	
	}
	printf("After ... \nLength : %d\n",SeqQueue_Length(queue));
	printf("Header : %d\n",*((int*)SeqQueue_Header(queue)));
	
	while(SeqQueue_Length(queue)>0)
	{
		printf("Retrieve : %d\n",*((int*)SeqQueue_Retrieve(queue)));	
	}
	printf("After ... \nLength : %d\n",SeqQueue_Length(queue));

	SeqQueue_Destroy(queue);
	return 0;
}
