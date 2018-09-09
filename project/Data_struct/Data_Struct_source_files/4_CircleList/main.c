#include <stdio.h>
#include <stdlib.h>
#include "CircleList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Value
{
	CircleListNode header;
	int v;
};
int main(int argc, char *argv[]) 
{
	CircleList* list = CircleList_Create();
	
	printf("Length : %d\n",CircleList_Length(list));
	
	struct Value v1;
	struct Value v2;
	struct Value v3;
	struct Value v4;
	
	v1.v = 1;
	v2.v = 2;
	v3.v = 3;
	v4.v = 4;
	
	int index = 0;
	
	CircleList_Insert(list,(CircleListNode*)&v1,CircleList_Length(list));//用尾插法时，能够实现循环链表 
	CircleList_Insert(list,(CircleListNode*)&v2,CircleList_Length(list));
	CircleList_Insert(list,(CircleListNode*)&v3,CircleList_Length(list));
	CircleList_Insert(list,(CircleListNode*)&v4,CircleList_Length(list));
	
	printf("Length : %d\n",CircleList_Length(list));
	
	for(index=0;index<3*CircleList_Length(list);index++)
	{
		struct Value* pv = (struct Value*)CircleList_Get(list,index);
		printf("[%d] : %d\n",index,pv->v);	
	}
	while(CircleList_Length(list))
	{
		struct Value* pv = (struct Value*)CircleList_Delete(list,0);
		printf("delete : %d\n",pv->v);	
	}
	printf("Length : %d\n",CircleList_Length(list));
	
	CircleList_Insert(list,(CircleListNode*)&v1,0);//用头插法时，能够实现循环链表 
	CircleList_Insert(list,(CircleListNode*)&v2,0);
	CircleList_Insert(list,(CircleListNode*)&v3,0);
	CircleList_Insert(list,(CircleListNode*)&v4,0);
	
	printf("Length : %d\n",CircleList_Length(list));
	
	printf("delete the first ...\n");
	
	CircleList_Delete(list,0);
	
	for(index=0;index<3*CircleList_Length(list);index++)
	{
		struct Value* pv = (struct Value*)CircleList_Get(list,index);
		printf("[%d] : %d\n",index,pv->v);	
	}
	
	printf("delete the v3 ...\n");
	
	CircleList_DeleteNode(list,(CircleListNode*)&v3);
	
	for(index=0;index<3*CircleList_Length(list);index++)
	{
		struct Value* pv = (struct Value*)CircleList_Get(list,index);
		printf("[%d] : %d\n",index,pv->v);	
	}
	
	printf("Rest node : %d\n",((struct Value*)CircleList_Reset(list))->v);
	printf("Current node : %d\n",((struct Value*)CircleList_Current(list))->v);
	printf("Current node next: %d\n",((struct Value*)CircleList_Next(list))->v);
	printf("Current node : %d\n",((struct Value*)CircleList_Current(list))->v);
	printf("Rest node : %d\n",((struct Value*)CircleList_Reset(list))->v);
	printf("Current node : %d\n",((struct Value*)CircleList_Current(list))->v);
	
	CircleList_Destroy(list);
	return 0;
}
