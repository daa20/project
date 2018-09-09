#include "LinkQueue.h"
#include "LinkList.h"
#include <malloc.h>

typedef struct _tag_LinkQueue
{
	LinkListNode header;
	void* item;
}TLinkQueueNode;

LinkQueue* LinkQueue_Create()
{
	return LinkList_Create();
}

void LinkQueue_Destroy(LinkQueue* queue)
{
	LinkQueue_Clear(queue);
	LinkList_Destroy(queue);
}
void LinkQueue_Clear(LinkQueue* queue)
{
	if(queue!=NULL)
	{
		while(LinkQueue_Length(queue)>0)
		{
			LinkQueue_Retrieve(queue);	
		}	
	}	
}

int LinkQueue_Length(LinkQueue* queue)
{
	return LinkList_Length(queue);
}

int LinkQueue_Append(LinkQueue* queue,void* item)
{
	int ret = 0;
	TLinkQueueNode* node = (TLinkQueueNode*)malloc(sizeof(TLinkQueueNode));
	ret = (node!=NULL)&&(item!=NULL);
	if(ret)
	{
		node->item = item;
		ret = LinkList_Insert(queue,(LinkListNode*)node,LinkList_Length(queue));	
	}
	if(ret==0)
	{
		free(node);	
	}
	return ret;
}

void* LinkQueue_Retrieve(LinkQueue* queue)
{
	void* ret = NULL;
	TLinkQueueNode* node = (TLinkQueueNode*)malloc(sizeof(TLinkQueueNode));
	if(node!=NULL)
	{
		node = (TLinkQueueNode*)LinkList_Delete(queue,0);
		ret = (void*)node->item;	
	}
	free(node);
	return ret;
}

void* LinkQueue_Header(LinkQueue* queue)
{
	void* ret = NULL;
	TLinkQueueNode* node = (TLinkQueueNode*)LinkList_Get(queue,0);
	if(node!=NULL)
	{
		ret = node->item;	
	}
	return ret;
}
