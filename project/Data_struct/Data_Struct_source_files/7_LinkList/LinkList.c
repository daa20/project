#include "LinkList.h"
#include <malloc.h>

typedef struct _tag_DLinkList
{
	DLinkListNode header;
	DLinkListNode* slider;
	int length;
}TDLinkList;

DLinkList* DLinkList_Create()
{
	TDLinkList* ret = (TDLinkList*)malloc(sizeof(TDLinkList));
	if(ret!=NULL)
	{
		ret->header.pre = NULL;
		ret->header.next = NULL;
		ret->slider = NULL;
		ret->length = 0;	
	}
	
	return ret;
}

void DLinkList_Destroy(DLinkList* list)
{
	free(list);
}

void DLinkList_Clear(DLinkList* list)
{
	TDLinkList* sList = (TDLinkList*)list;
	if(sList!=NULL)
	{
		sList->header.pre = NULL;
		sList->header.next = NULL;
		sList->slider = NULL;
		sList->length = 0;	
	}
}

int DLinkList_Length(DLinkList* list)
{
	int ret = 0;
	TDLinkList* sList = (TDLinkList*)list;
	if(sList!=NULL)
	{
		ret = sList->length;	
	}
	return ret;
}

int DLinkList_Insert(DLinkList* list,DLinkListNode* node,int pos)
{
	int ret = 0;
	TDLinkList* sList = (TDLinkList*)list;
	ret = (sList!=NULL)&&(node!=NULL)&&(pos>=0);
	if(ret)
	{
		if(pos>sList->length)
		{
			pos = sList->length;	
		}
		int i = 0;
		DLinkListNode* current = (DLinkListNode*)sList;
		DLinkListNode* next = NULL;
		for(i=0;i<pos;i++)
		{
			current = current->next;	
		}	
		next = current->next;
		
		current->next = node;
		node->next = next;
		if(next!=NULL)
		{
			next->pre = node;	
		}
		
		node->pre = current;
		if(sList->length==0)
		{
			node->pre = NULL;
			sList->slider = node;	
		}
		sList->length++;
	}
	return ret;
}

DLinkListNode* DLinkList_Get(DLinkList* list,int pos)
{
	DLinkListNode* ret = NULL;
	TDLinkList* sList = (TDLinkList*)list;
	if((sList!=NULL)&&(pos>=0)&&(pos<sList->length))
	{
		int i = 0;
		DLinkListNode* current = (DLinkListNode*)sList;
		for(i=0;i<pos;i++)
		{
			current = current->next;	
		}	
		ret = current->next;
	}
	
	return ret;
}

DLinkListNode* DLinkList_Delete(DLinkList* list,int pos)
{
	DLinkListNode* ret = NULL;
	TDLinkList* sList = (TDLinkList*)list;
	DLinkListNode* first = (DLinkListNode*)sList->header.next;
	DLinkListNode* last = (DLinkListNode*)DLinkList_Get(sList,sList->length-1);
	if((sList!=NULL)&&(pos>=0)&&(pos<sList->length))
	{
		int i = 0;
		DLinkListNode* current = (DLinkListNode*)sList;
		DLinkListNode* next = NULL;
		for(i=0;i<pos;i++)
		{
			current = current->next;	
		}	
		ret = current->next;
		if(ret!=NULL)
		{
			next = ret->next;	
		}
		
		current->next = next;
		if(next!=NULL)
		{
			next->pre = current;
			if(current==(DLinkListNode*)sList)
			{
				next->pre = NULL;	
			}	
		}
		if(ret == sList->slider)
		{
			sList->slider = next;	
		}
		
		sList->length--;
	}
	return ret;
}
