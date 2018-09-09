#include "CircleList.h"
#include <malloc.h>
#include <stdio.h>

typedef struct _tag_CircleList
{
	CircleListNode header;
	CircleListNode* slider;
	int length;	
}TCircleList;

CircleList* CircleList_Create()
{
	TCircleList* ret = (TCircleList*)malloc(sizeof(TCircleList));
	if(ret!=NULL)
	{
		ret->header.next = NULL;
		ret->slider = NULL;
		ret->length = 0;	
	}
	return ret;
}

void CircleList_Destroy(CircleList* list)
{
	free(list);
}
void CircleList_Clear(CircleList* list)
{
	TCircleList* sList = (TCircleList*)list;
	if(sList!=NULL)
	{
		sList->header.next = NULL;
		sList->slider = NULL;
		sList->length = 0;	
	}
}

int CircleList_Length(CircleList* list)
{
	TCircleList* sList = (TCircleList*)list;
	int ret = 0;
	if(sList!=NULL)
	{
		ret = sList->length;	
	}
	return ret;
}

int CircleList_Insert(CircleList* list,CircleListNode* node,int pos)
{
	int ret = 0;
	TCircleList* sList = (TCircleList*)list;
	ret = (sList!=NULL)&&(node!=NULL)&&(pos>=0);
	int i = 0;
	if(ret)
	{
		if(pos > sList->length)
		{
			pos = sList->length;	
		}
		CircleListNode* current = (CircleListNode*)sList;
		for(i=0;i<pos;i++)
		{
			current = current->next;   //头插法时，要执行一次程序 
		}
		node->next = current->next;
		current->next = node;
		if(sList->length==0) 
		{
			sList->slider = node;
			node->next = node;    //当且进当使用尾插法时，能够实现循环链表 	
		}
		sList->length++;	
	}
	return ret;
}

CircleListNode* CircleList_Get(CircleList* list,int pos)
{
	CircleListNode* ret = NULL;
	TCircleList* sList = (TCircleList*)list;
	int i = 0;
	if((sList!=NULL)&&(pos>=0)/*&&(pos<sList->length)*/)
	{		
		CircleListNode* current = (CircleListNode*)sList;	
		for(i=0;i<pos;i++)
		{
			current = current->next;	
		}
		ret = current->next;
	}
	return ret;
}
CircleListNode* CircleList_Delete(CircleList* list,int pos)
{
	CircleListNode* ret = NULL;
	TCircleList* sList = (TCircleList*)list;
	int i = 0;
	if((sList!=NULL)&&(pos>=0))
	{
		CircleListNode* current = (CircleListNode*)sList;
		CircleListNode* first = sList->header.next;
		CircleListNode* last = (CircleListNode*)CircleList_Get(sList,sList->length-1);
		for(i=0;i<pos;i++)
		{
			current = current->next;	
		}	
		ret = current->next;
		current->next = ret->next;
		sList->length--;
		
		if(first==ret)
		{
			sList->header.next = ret->next;
			last->next = ret->next;
		}
		if(sList->slider==ret)
		{
			sList->slider = ret->next;	
		}
		if(sList->length==0)
		{
			sList->slider = NULL;
			sList->header.next = NULL;	
		}		
	}
	return ret;
}

CircleListNode* CircleList_DeleteNode(CircleList* list,CircleListNode* node)
{
	CircleListNode* ret = NULL;
	TCircleList* sList = (TCircleList*)list;
	int i = 0;
	if((sList!=NULL)&&(node!=NULL))
	{
		CircleListNode* current = (CircleListNode*)sList;
		for(i=0;i<sList->length;i++)
		{
			if(current->next == node)
			{
				ret = current->next;
				break;		
			}
			current = current->next;
		}
		if(ret!=NULL)
		{
			CircleList_Delete(sList,i);			
		}			
	}
	return ret;
}


CircleListNode* CircleList_Reset(CircleList* list)
{
	CircleListNode* ret = NULL;
	TCircleList* sList = (TCircleList*)list;
	if(sList!=NULL)
	{
		sList->slider = sList->header.next;	
		ret = sList->slider;
	}
	return ret;
}

CircleListNode* CircleList_Current(CircleList* list)
{
	CircleListNode* ret = NULL;
	TCircleList* sList = (TCircleList*)list;
	if(sList!=NULL)
	{
		ret = sList->slider;		
	}
	return ret;
}

CircleListNode* CircleList_Next(CircleList* list)
{
	CircleListNode* ret = NULL;
	TCircleList* sList = (TCircleList*)list;
	if((sList!=NULL)&&(sList->slider!=NULL))
	{
		ret = sList->slider;
		sList->slider = ret->next;	
	}
	return ret;
}
