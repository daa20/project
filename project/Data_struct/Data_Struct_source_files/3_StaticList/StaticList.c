#include "StaticList.h"
#include <malloc.h>

#define AVAILABLE -1

typedef struct _tag_StaticListNode
{
	unsigned int data;
	int next;
}TStaticListNode;
typedef struct _tag_StaticList
{
	int capacity;
	TStaticListNode header;
	TStaticListNode node[];
}TStaticList;

StaticList* StaticList_Create(int capacity)
{
	TStaticList* ret = NULL;
	int i = 0;
//	printf("%d ,%d\n",sizeof(TStaticList),sizeof(TStaticListNode));
	if(capacity>0)
	{
		ret = (TStaticList*)malloc(sizeof(TStaticList)+(capacity+1)*sizeof(TStaticListNode));	
		if(ret!=NULL)
		{
			ret->capacity = capacity;
			ret->header.data = 0;   //length
			ret->header.next = 0;	
			for(i=1;i<=capacity;i++)
			{
				ret->node[i].next = AVAILABLE;	
			}
		}
	}
	return ret;		
}
void StaticList_Destroy(StaticList* list)
{
	free(list);
}
void StaticList_Clear(StaticList* list)
{
	TStaticList* sList = (TStaticList*)list;
	int i = 0;
	if(sList!=NULL)
	{
		sList->header.data = 0;
		sList->header.next = 0;	
		for(i=1;i<=sList->capacity;i++)
		{
			sList->node[i].next = AVAILABLE;	
		}
	}
}
int StaticList_Length(StaticList* list)
{
	int ret = 0;
	TStaticList* sList = (TStaticList*)list;
	if(sList!=NULL)
	{
		ret = sList->header.data;	
	}
	return ret;
}
int StaticList_Capacity(StaticList* list)
{
	int ret = 0;
	TStaticList* sList = (TStaticList*)list;
	if(sList!=NULL)
	{
		ret = sList->capacity;	
	}
	return ret;
}
int StaticList_Insert(StaticList* list,StaticListNode* node,int pos)
{
	int ret = 0;
	TStaticList* sList = (TStaticList*)list;
	ret = (sList!=NULL)&&(node!=NULL)&&(pos>=0)&&(sList->header.data+1 <= sList->capacity);
	int i = 0;
	int index = 0;
	int current = 0;
	if(ret)
	{
		for(i=1;i<=sList->capacity;i++)
		{
			if(sList->node[i].next == AVAILABLE)
			{
				index = i;
				break;	
			}	
		}
		sList->node[index].data = (unsigned int)node;
		sList->node[0] = sList->header;
		for(i=0;(i<pos)&&(sList->node[current].next!=0);i++)
		{
			current = sList->node[current].next;	
		}		
		
		sList->node[index].next = sList->node[current].next;
		sList->node[current].next = index;
		
		sList->node[0].data++;
		
		sList->header = sList->node[0];  //updata the length 	
	}
	return ret;
}

StaticListNode* StaticList_Get(StaticList* list,int pos)
{
	StaticListNode* ret = NULL;
	TStaticList* sList = (TStaticList*)list;
	int i = 0;
	int current = 0;
	int object = 0;
	
	if((sList!=NULL)&&(pos>=0)&&(pos < sList->header.data))
	{
		sList->node[0] = sList->header;
		for(i=0;i<pos;i++)
		{
			current = sList->node[current].next;	
		}	
		object = sList->node[current].next;
		ret = (StaticListNode*)(sList->node[object].data);
	}
	return ret;
}

StaticListNode* StaticList_Delete(StaticList* list,int pos)
{
	StaticListNode* ret = NULL;
	TStaticList* sList = (TStaticList*)list;
	int i = 0;
	int current = 0;
	int object = 0;
	if((sList!=NULL)&&(pos>=0)&&(pos<sList->header.data))
	{
		sList->node[0] = sList->header;
		for(i=0;i<pos;i++)
		{
			current = sList->node[current].data;	
		}
		object = sList->node[current].next;
		sList->node[current].next = sList->node[object].next;
		sList->node[0].data--;
		sList->header = sList->node[0];
		sList->node[object].next = AVAILABLE;
		ret = (StaticListNode*)(sList->node[object].data);
	}
	return ret;
}
