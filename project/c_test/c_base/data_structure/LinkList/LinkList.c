#include <stdlib.h>

#include "LinkList.h"


typedef struct _tag_LinkList {
    LinkListNode    header;
    int             length;
} TLinkList;


LinkList *
LinkList_Create(void)
{
    TLinkList *ret = NULL;

    ret = (TLinkList *)malloc(sizeof(TLinkList));

    if (ret != NULL) {
        ret->header.next = NULL;
        ret->length = 0;
    }

    return ret;
}

void 
LinkList_Destroy(LinkList *list) 
{
    free(list);
}

void
LinkList_Clear(LinkList *list)
{
    TLinkList *sList = (TLinkList *)list;

    if (sList != NULL) {
        sList->header.next = NULL;
        sList->length = 0;
    }
}

int 
LinkList_Length(LinkList *list) 
{
    TLinkList   *sList = (TLinkList *)list;
    int         ret = -1;

    if (sList != NULL) {
        ret = sList->length;
    }

    return ret;
}

int
LinkList_Insert(LinkList *list, LinkListNode *node, int pos)
{
    TLinkList   *sList = (TLinkList *)list;
    int         ret = 0;
    int         i = 0;
    LinkListNode *current;

    ret = (sList != NULL) && (node != NULL) && (pos >= 0);
    
    if (ret != 0) {
    
        current = (LinkListNode *)sList;
        for (i = 0; (i < pos) && (current->next != NULL); i++) {
            current = current->next;
        }

        node->next = current->next;
        current->next = node;

        sList->length++;
    }

    return ret;
}


LinkListNode *
LinkList_Get(LinkList *list, int pos) 
{
    LinkListNode    *ret = NULL;
    TLinkList       *sList = (TLinkList *)list;
    int             i = 0;

    if ((sList != NULL) && (pos >= 0) && (pos < sList->length)) {
        LinkListNode *current = (LinkListNode *)sList;
        for (i = 0; i < pos; i++) {
        
            current = current->next;
        }

        ret = current->next;
    }

    return ret;
}

LinkListNode *
LinkList_Delete(LinkList *list, int pos)
{
    LinkListNode    *ret = NULL;
    TLinkList       *sList = (TLinkList *)list;
    int             i = 0;
    LinkListNode    *current = NULL;

    if ((sList != NULL) && (pos >= 0) && (pos < sList->length)) {
        
        current = (LinkListNode *)sList;
        for (i = 0; i < pos; i++) {
            current = current->next;
        }

        ret = current->next;

        current->next = ret->next;

        sList->length--;
    }

    return ret;
}
