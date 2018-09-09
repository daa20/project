#include <stdio.h>
#include <stdlib.h>
#include "SeqStack.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	SeqStack* stack = SeqStack_Create(10);
	
	printf("Capacity: %d\n",SeqStack_Capacity(stack));
	printf("Size : %d\n",SeqStack_Size(stack));
	
	int i = 0;
	int a[10];
	
	for(i=0;i<10;i++)
	{
		a[i] = i;
		SeqStack_Push(stack,a+i);	
	}

	printf("Size : %d\n",SeqStack_Size(stack));
	printf("Top: %d\n", *(int*)SeqStack_Top(stack));
	
	while(SeqStack_Size(stack)>0)
	{
		printf("Pop : %d\n",*((int*)SeqStack_Pop(stack)));	
	}
	
	SeqStack_Destroy(stack);
	return 0;
}
