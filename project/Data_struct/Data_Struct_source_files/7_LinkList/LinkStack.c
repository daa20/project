#include "LinkList.h"
#include "LinkStack.h"
#include <malloc.h>

typedef struct _tag_DLinkStackNode
{
	DLinkListNode header;
	void* item;
}TDLinkStackNode;

DLinkStack* DLinkStack_Create()
{
	return DLinkList_Create();
}


void DLinkStack_Destroy(DLinkStack* stack)
{
	DLinkStack_Clear(stack);
	DLinkList_Destroy(stack);
}

void DLinkStack_Clear(DLinkStack* stack)
{
	
	while(DLinkStack_Length(stack)>0)
	{
		DLinkStack_Pop(stack);	
	}
}

int DLinkStack_Length(DLinkStack* stack)
{
	return DLinkList_Length(stack);
}

int DLinkStack_Push(DLinkStack* stack,void* item)
{
	int ret = 0;
	TDLinkStackNode* node = (TDLinkStackNode*)malloc(sizeof(TDLinkStackNode));
	ret = (node!=NULL)&&(item!=NULL);
	if(ret)
	{
		node->item = item;
		ret = DLinkList_Insert(stack,(DLinkListNode*)node,0);	
	}
	if(ret==0)
	{
		free(node);	
	}
	return ret;
}

void* DLinkStack_Pop(DLinkStack* stack)
{
	void* ret = NULL;
	TDLinkStackNode* node = (TDLinkStackNode*)DLinkList_Delete(stack,0);
	if(node!=NULL)
	{
		ret = node->item;
		free(node);	//这里可以free	 
	}
	
	return ret;
}

void* DLinkStack_Top(DLinkStack* stack)
{
	void* ret = NULL;
	TDLinkStackNode* node = (TDLinkStackNode*)DLinkList_Get(stack,0);
	if(node!=NULL)
	{
		ret = node->item;
//		free(node);  //这里不能free	
	}
	return ret;
}

