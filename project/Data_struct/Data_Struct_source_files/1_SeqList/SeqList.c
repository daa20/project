#include "SeqList.h"
#include <malloc.h>
typedef unsigned int TSeqListNode;

typedef struct _tag_SeqList
{
	int capacity;
	int length;
	TSeqListNode* node;	
} TSeqList;

SeqList* SeqList_Create(int capacity)
{
	TSeqList* ret = NULL;
	if(capacity > 0)
	{
		ret = (TSeqList*)malloc(sizeof(TSeqList) + capacity*sizeof(TSeqListNode));
		if(ret!=NULL)
		{
			ret->capacity = capacity;
			ret->length = 0;
			ret->node = (TSeqListNode*)(ret + 1);	
		}	
	}
	return ret;
}
void SeqList_Destroy(SeqList* list)
{
	free(list);
}
void SeqList_Clear(SeqList* list)
{
	TSeqList* sList = (TSeqList*)list;
	if(sList!=NULL)
	{
		sList->length = 0;
	}
}
int SeqList_Capacity(SeqList* list)
{
	int ret = 0;
	TSeqList* sList = (TSeqList*)list;
	if(sList!=NULL)
	{
		ret = sList->capacity;	
	}
	return ret;
}
int SeqList_Length(SeqList* list)
{
	int ret = 0;
	TSeqList* sList = (TSeqList*)list;
	if(sList!=NULL)
	{
		ret = sList->length;	
	}
	return ret;
}
int SeqList_Insert(SeqList* list,SeqListNode* node,int pos)
{
	int ret = 0;
	TSeqList* sList = (TSeqList*)list;
	ret = (sList!=NULL)&&(node!=NULL)&&(sList->length+1 <= sList->capacity);
	ret = ret&&(pos>=0);
	int i = 0;
	if(ret)
	{
		if(pos>sList->length)
		{
			pos = sList->length;	
		}
		for(i=sList->length;i>pos;i--)
		{
			sList->node[i] = sList->node[i-1];	
		}		
		
		sList->node[pos] = (TSeqListNode)node;
		sList->length++;
	}
	return ret;
}

SeqListNode* SeqList_Get(SeqList* list,int pos)
{
	SeqListNode* ret = NULL;
	TSeqList* sList = (TSeqList*)list;
	if((sList!=NULL)&&(pos>=0)&&(pos<sList->length))
	{
		ret = (SeqListNode*)sList->node[pos];
	}
	return ret;
}

SeqListNode* SeqList_Delete(SeqList* list,int pos)
{
	SeqListNode* ret = NULL;
	TSeqList* sList = (TSeqList*)list;
	int i = 0;
	if((sList!=NULL)&&(pos<sList->length))
	{
		ret = (SeqListNode*)sList->node[pos];
		for(i=pos+1;i<sList->length;i++)
		{
			sList->node[i-1] = sList->node[i];	
		}
		sList->length--;	
	}
	return ret;
}
