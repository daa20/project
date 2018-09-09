#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Value
{
	LinkListNode header;
	int v;
};
int main(int argc, char *argv[]) 
{
	LinkList* list = LinkList_Create();
	printf("The Length is : %d\n",LinkList_Length(list));
	struct Value v1;
	struct Value v2;
	struct Value v3;
	struct Value v4;
	v1.v = 1;
	v2.v = 2;
	v3.v = 3;
	v4.v = 4;
	
	int index = 0;
	
	LinkList_Insert(list,(LinkListNode*)&v1,LinkList_Length(list));
	LinkList_Insert(list,(LinkListNode*)&v2,LinkList_Length(list));
	LinkList_Insert(list,(LinkListNode*)&v3,LinkList_Length(list));
	LinkList_Insert(list,(LinkListNode*)&v4,LinkList_Length(list));
	
	printf("The Length is : %d\n",LinkList_Length(list));
	
	for(index=0;index<LinkList_Length(list);index++)
	{
		struct Value* pv = (struct Value*)LinkList_Get(list,index);
		printf("[%d] : %d\n",index,pv->v);	
	}
	
	while(LinkList_Length(list)>0)
	{
		struct Value* pv = (struct Value*)LinkList_Delete(list,0);
		printf("[delete] : %d\n",pv->v);	 	
	}
	printf("The Length is : %d\n",LinkList_Length(list));
	LinkList_Destroy(list);
	return 0;
}
