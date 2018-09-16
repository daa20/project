#include <stdlib.h>

#include "CircleList.h"


typedef struct _tag_CircleList {
    CircleListNode  header;
    CircleListNode  *slider;
    int             length;
} TCircleList;


CircleList *
CircleList_Create(void)
{
    TCircleList     *ret = NULL;

    ret = (TCircleList *)malloc(sizeof(TCircleList));

    if (ret != NULL) {
        ret->header.next = NULL;
        ret->slider = NULL;
        ret->length = 0;
    }

    return ret;
}

void
CircleList_Destroy(CircleList *list)
{
    free(list);
}

void 
CircleList_Clear(CircleList *list)
{
    TCircleList *sList = (TCircleList *)list;

    if (sList != NULL) {
        sList->header.next = NULL;
        sList->slider = NULL;
        sList->length = 0;
    }
}


int
CircleList_Length(CircleList *list)
{
    int ret = -1;
    TCircleList *sList = (TCircleList *)list;

    if (sList != NULL) {
        ret = sList->length;
    }

    return ret;
}

int 
CircleList_Insert(CircleList *list, CircleListNode *node, int pos)
{
    int             ret = -1;
    int             i = 0;
    TCircleList     *sList = (TCircleList *)list;

    if ((sList != NULL) && (node != NULL) && (pos >= 0)) {
        CircleListNode *current = (CircleListNode *)sList;
        for (i = 0; (i < pos) && (current->next != NULL); i++) {
            current = current->next;
        }

        node->next = current->next;
        current->next = node;

        if (sList->length == 0) {
            sList->slider = node;
            node->next = node;
        }

        sList->length++;

    }
    return ret;
}

CircleListNode *
CircleList_Get(CircleList *list, int pos)
{
    CircleListNode  *ret = NULL;
    TCircleList     *sList = (TCircleList *)list;
    int             i = 0;

    if ((sList != NULL) && (pos >= 0) /*&& (pos < sList->length)*/) {
    
        CircleListNode *current = (CircleListNode *)sList;
        for (i = 0; i < pos; i++) {
        
            current = current->next;
        }

        ret = current->next;
    
    }

    return ret;
}

CircleListNode *
CircleList_Delete(CircleList *list, int pos)
{
    CircleListNode  *ret = NULL;
    TCircleList     *sList = (TCircleList *)list;
    int             i = 0;

    if ((sList != NULL) && (pos >= 0)) {
        CircleListNode *current = (CircleListNode *)sList;
        CircleListNode *first = sList->header.next;
        CircleListNode *last = CircleList_Get(sList, sList->length - 1);

        for (i = 0; i < pos; i++) {
            current = current->next;
        }

        ret = current->next;
        
        current->next = ret->next;

        sList->length--;

        if (ret == first) {
            sList->header.next = ret->next;
            last->next = ret->next;
        }

        if (ret == sList->slider) {
            sList->slider = ret->next;
        }

        if (sList->length == 0) {
            sList->header.next = NULL;
            sList->slider = NULL;
        }
    
    }


    return ret;
}

CircleListNode *
CircleList_DeleteNode(CircleList *list, CircleListNode *node) 
{
    CircleListNode  *ret = NULL;
    TCircleList     *sList = (TCircleList *)list;
    int             i = 0;
    
    if ((sList != NULL) && (node != NULL)) {
    
        CircleListNode *current = (CircleListNode *)sList;

        for (i = 0; i < sList->length; i++) {

            if (current->next == node) {
                ret = current->next;
                break;
            }

            current = current->next;
        }

        if (ret != NULL) {
            CircleList_Delete(sList, i);
        }
    }

    return ret;

}


CircleListNode *
CircleList_Reset(CircleList *list)
{
    CircleListNode  *ret = NULL;
    TCircleList     *sList = (TCircleList *)list;

    if (sList != NULL) {
        sList->slider = sList->header.next;
        ret = sList->slider;
    
    }

    return ret;
}

CircleListNode *
CircleList_Current(CircleList *list)
{
    CircleListNode  *ret = NULL;
    TCircleList     *sList = (TCircleList *)list;

    if (sList != NULL) {
    
        ret = sList->slider;
    }

    return ret;
}


CircleListNode *
CircleList_Next(CircleList *list)
{
    CircleListNode  *ret = NULL;
    TCircleList     *sList = (TCircleList *)list;

    if (sList != NULL) {
        ret = sList->slider;
        sList->slider = ret->next;
    }

    return ret;


}

