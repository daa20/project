#include <stdlib.h>

#include "DLinkList.h"

typedef struct _tag_TDLinkList_t {
    DLinkListNode   header;
    DLinkListNode   *slider;
    int             length;
} TDLinkList;

DLinkList *DLinkList_Create(void)
{
    TDLinkList *ret = NULL;
    
    ret = (TDLinkList *)malloc(sizeof(TDLinkList));

    if (ret != NULL) {
        ret->header.prev = NULL;
        ret->header.next = NULL;
        ret->slider = NULL;
        ret->length = 0;
    }

    return ret;
}


void
DLinkList_Destroy(DLinkList *list)
{
    free(list);
}

void 
DLinkList_Clear(DLinkList *list)
{
    TDLinkList *sList = (TDLinkList *)list;

    if (sList != NULL) {
        sList->header.prev = NULL;
        sList->header.next = NULL;
        sList->slider = NULL;
        sList->length = 0;
    }
}

int 
DLinkList_Length(DLinkList *list)
{
    TDLinkList *sList = (TDLinkList *)list;
    int         ret = 0;
    
    if (sList != NULL) {
        ret = sList->length;
    }

    return ret;
}

int
DLinkList_Insert(DLinkList *list, DLinkListNode *node, int pos)
{
    int ret = -1;
    int i = 0;
    TDLinkList *sList = (TDLinkList *)list;

    ret = (sList != NULL) && (node != NULL) && (pos >= 0);

    if (ret != 0) {
        DLinkListNode *current = (DLinkListNode *)sList;
        DLinkListNode *next = NULL;

        for (i = 0; i < pos; i++) {
            current = current->next;
        }

        next = current->next;

        current->next = node;
        node->next = next;
        if (next != NULL) {
            next->prev = node;
        }

        node->prev = current;

        if (sList->length == 0) {
            sList->slider = node;
            node->prev = NULL;
        }

        sList->length++;
    }


    return ret;
}

DLinkListNode *
DLinkList_Get(DLinkList *list, int pos)
{
    DLinkListNode   *ret = NULL;
    TDLinkList      *sList = (TDLinkList *)list;
    int             i = 0;

    if ((sList != NULL) && (pos >= 0) && (pos < sList->length)) {
        DLinkListNode *current = (DLinkListNode *)sList;

        for (i = 0; i < pos; i++) {
            current = current->next;
        }

        ret = current->next;
    
    }

    return ret;
}

DLinkListNode *
DLinkList_Delete(DLinkList *list, int pos) 
{
    DLinkListNode   *ret = NULL;
    TDLinkList      *sList = (TDLinkList *)list;
    int             i = 0;

    if ((sList != NULL) && (pos >= 0) && (pos < sList->length)) {
        DLinkListNode *current = (DLinkListNode *)sList;
        DLinkListNode *next = NULL;

        for (i = 0; i < pos; i++) {
        
            current = current->next;
        }

        ret = current->next;

        next = ret->next;

        current->next = next;
        if (next != NULL) {
            next->prev = current;
            if (current == (DLinkListNode *)sList) {
                next->prev = NULL;
            }
        }
        
        if (ret == sList->slider) {
            sList->slider = ret->next;
        }
        
        sList->length--;
    }

    return ret;
}


DLinkListNode *
DLinkLink_DeleteNode(DLinkList *list, DLinkListNode *node)
{
    DLinkListNode *ret = NULL;
    TDLinkList      *sList = (TDLinkList *)list;
    int             i = 0;

    if ((sList != NULL) && (node != NULL)) {
        DLinkListNode *current = (DLinkListNode *)sList;

        for (i = 0; i < sList->length; i++) {
            
            if (current->next == node) {
                ret = current->next;
                break;
            }
            
            current = current->next;
        }

        if (ret != NULL) {
            DLinkList_Delete(sList, i);
        }
    }

    return ret;
}

DLinkListNode *
DLinkList_Reset(DLinkList *list)
{
    TDLinkList      *sList = (TDLinkList *)list;
    DLinkListNode   *ret = NULL;

    if (sList != NULL) {
        sList->slider = sList->header.next;
        ret = sList->slider;
    }

    return ret;

}

DLinkListNode *
DLinkList_Current(DLinkList *list)
{
    DLinkListNode *ret = NULL;
    TDLinkList      *sList = (TDLinkList *)list;

    if (sList != NULL) {
        ret = sList->slider;
    }

    return ret;
}

DLinkListNode *
DLinkList_Next(DLinkList *list) 
{
    DLinkListNode *ret = NULL;
    TDLinkList      *sList = (TDLinkList *)list;

    if ((sList != NULL) && (sList->slider != NULL)) {
        ret = sList->slider;
        sList->slider = ret->next;
    }
    return ret;
}

DLinkListNode *
DLinkList_Prev(DLinkList *list)
{
    DLinkListNode *ret = NULL;
    TDLinkList      *sList = (TDLinkList *)list;

    if ((sList != NULL) && (sList->slider != NULL)) {
        ret = sList->slider;
        sList->slider = ret->prev;
    }
    return ret;
}

