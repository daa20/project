#ifndef _LINKLIST_H_
#define _LINKLIST_H_

typedef struct _tag_DLinkListNode DLinkListNode;
struct _tag_DLinkListNode
{
	DLinkListNode* pre;
	DLinkListNode* next;
};

typedef void DLinkList;

DLinkList* DLinkList_Create();

void DLinkList_Destroy(DLinkList* list);

void DLinkList_Clear(DLinkList* list);

int DLinkList_Length(DLinkList* list);

int DLinkList_Insert(DLinkList* list,DLinkListNode* node,int pos);

DLinkListNode* DLinkList_Get(DLinkList* list,int pos);

DLinkListNode* DLinkList_Delete(DLinkList* list,int pos);

#endif
