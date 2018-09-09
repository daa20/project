#include <stdio.h>
#include <stdlib.h>
#include "DLinkList.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Value
{
	DLinkListNode header;
	int v;	
};

int main(int argc, char *argv[]) 
{
	DLinkList* list = DLinkList_Create();
	printf("Length: %d\n",DLinkList_Length(list));
	
	struct Value v1;
	struct Value v2;
	struct Value v3;
	struct Value v4;
	struct Value v5;
	struct Value v6;
	
	v1.v = 1;
	v2.v = 2;
	v3.v = 3;
	v4.v = 4;
	v5.v = 5;
	v6.v = 6;
	
	int index = 0;
	
	DLinkList_Insert(list,(DLinkListNode*)&v1,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v2,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v3,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v4,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v5,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v6,DLinkList_Length(list));	
	
	printf("Length: %d\n",DLinkList_Length(list));
	
	for(index=0;index<DLinkList_Length(list);index++)
	{
		struct Value* pv = (struct Value*)DLinkList_Get(list,index);
		printf("[%d] : %d\n",index,pv->v);	
	}
	
	while(DLinkList_Length(list)>0)
	{
		struct Value* pv = (struct Value*)DLinkList_Delete(list,0);
		printf("[delete] : %d\n",pv->v);	
	}
	printf("Length: %d\n",DLinkList_Length(list));
	
	DLinkList_Insert(list,(DLinkListNode*)&v1,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v2,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v3,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v4,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v5,DLinkList_Length(list));
	DLinkList_Insert(list,(DLinkListNode*)&v6,DLinkList_Length(list));	
	
	printf("Length: %d\n",DLinkList_Length(list));
	
	DLinkList_DeleteNode(list,(DLinkListNode*)&v1);
	
    printf("Length: %d\n",DLinkList_Length(list));
	
	for(index=0;index<DLinkList_Length(list);index++)
	{
		struct Value* pv = (struct Value*)DLinkList_Get(list,index);
		printf("[%d] : %d\n",index,pv->v);	
	}

//	for(index=0;index<DLinkList_Length(list);index++)
//	{
//		struct Value* pv = (struct Value*)DLinkList_Next(list);
//		printf("[%d] : %d\n",index,pv->v);	
//	}
	
	
	printf("\n");
    
    printf("[Reset] : %d\n",((struct Value*)DLinkList_Reset(list))->v);
	printf("[Next] : %d\n",((struct Value*)DLinkList_Next(list))->v);
	printf("[Current] : %d\n",((struct Value*)DLinkList_Current(list))->v);
	printf("[Pre] : %d\n",((struct Value*)DLinkList_Pre(list))->v);
	printf("[Current] : %d\n",((struct Value*)DLinkList_Current(list))->v);
	
	DLinkList_Destroy(list);
	return 0;
}
