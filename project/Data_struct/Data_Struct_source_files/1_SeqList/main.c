
#include <stdio.h>
#include <stdlib.h>
#include "SeqList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	SeqList* list = SeqList_Create(10);
	printf("The capacity is : %d\n",SeqList_Capacity(list));
	printf("The Length is : %d\n",SeqList_Length(list));
	
	int i = 1;
	int j = 2;
	int k = 3;
	int l = 4;
	int m = 5;
	int n = 6;
	
	int index = 0;
	
	printf("Insert some var...!\n");
	
	SeqList_Insert(list,(SeqListNode*)&i,SeqList_Length(list));
	SeqList_Insert(list,(SeqListNode*)&j,SeqList_Length(list));
	SeqList_Insert(list,(SeqListNode*)&k,SeqList_Length(list));
	SeqList_Insert(list,(SeqListNode*)&l,SeqList_Length(list));
	SeqList_Insert(list,(SeqListNode*)&m,SeqList_Length(list));
	SeqList_Insert(list,(SeqListNode*)&n,SeqList_Length(list));
	
	printf("The Length is : %d\n",SeqList_Length(list));
	
	for(index=0;index<SeqList_Length(list);index++)
	{
		unsigned int* pv = (unsigned int*)SeqList_Get(list,index);
		printf("[%d] : %d\n",index,*pv);	
	}	
	
	while(SeqList_Length(list)>0)
	{
		unsigned int* pv = (unsigned int*)SeqList_Delete(list,0);
		printf("delete : %d\n",*pv);	
	}
	
	printf("The capacity is : %d\n",SeqList_Capacity(list));
	printf("The Length is : %d\n",SeqList_Length(list));	
	
	printf("Insert some var...!\n");
	
	SeqList_Insert(list,(SeqListNode*)&l,SeqList_Length(list));
	SeqList_Insert(list,(SeqListNode*)&m,SeqList_Length(list));
	SeqList_Insert(list,(SeqListNode*)&n,SeqList_Length(list));
	
	printf("The Length is : %d\n",SeqList_Length(list));
	
	for(index=0;index<SeqList_Length(list);index++)
	{
		unsigned int* pv = (unsigned int*)SeqList_Get(list,index);
		printf("[%d] : %d\n",index,*pv);	
	}
	
	SeqList_Clear(list);
	
	printf("clear all!\n");
	
	printf("The capacity is : %d\n",SeqList_Capacity(list));
	printf("The Length is : %d\n",SeqList_Length(list));
	
	SeqList_Destroy(list);
	return 0;
}
