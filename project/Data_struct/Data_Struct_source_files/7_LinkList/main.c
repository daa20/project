#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	DLinkStack* stack = DLinkStack_Create();
	
	int i = 0;
	int a[10];
	
	for(i=0;i<10;i++)
	{
		a[i] = i;
		DLinkStack_Push(stack,a+i);	
	}
	printf("Length: %d\n",DLinkStack_Length(stack));
	printf("Top : %d\n",*((int*)DLinkStack_Top(stack)));
	
	while(DLinkStack_Length(stack)>0)
	{
		printf("Pop : %d\n",*((int*)DLinkStack_Pop(stack)));
	}
	
	DLinkStack_Destroy(stack);
	return 0;
}
