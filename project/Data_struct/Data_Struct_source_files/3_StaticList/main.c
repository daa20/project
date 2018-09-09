#include <stdio.h>
#include <stdlib.h>
#include "StaticList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	StaticList* list = StaticList_Create(10);
	
	printf("the length : %d, the capacity : %d\n",StaticList_Length(list),StaticList_Capacity(list));
	
	int i = 1;
	int j = 2;
	int k = 3;
	
	int index = 0;
	
	StaticList_Insert(list,(StaticListNode*)&i,StaticList_Length(list));
	StaticList_Insert(list,(StaticListNode*)&j,StaticList_Length(list));
	StaticList_Insert(list,(StaticListNode*)&k,StaticList_Length(list));
	
	for(index=0;index<StaticList_Length(list);index++)
	{
		int* pv = (int*)StaticList_Get(list,index);
		printf("[%d] : %d\n",index,*pv);	
	}
	
	printf("the length : %d, the capacity : %d\n",StaticList_Length(list),StaticList_Capacity(list));	
	
	while(StaticList_Length(list)>0)
	{
		int* pv = (int*)StaticList_Delete(list,0);
		printf("delete : %d \n",*pv);	
	}
	StaticList_Destroy(list);
	return 0;
}
