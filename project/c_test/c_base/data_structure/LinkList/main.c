#include <stdio.h>

#include "LinkList.h"

typedef struct _tag_Value {
    LinkListNode    header;
    int             v;
} Value_t;


int
main(int argc, char *const argv[])
{

    LinkList    *list = LinkList_Create();
    int         i = 0;

    Value_t     v1;
    Value_t     v2;
    Value_t     v3;
    Value_t     v4;
    Value_t     v5;

    v1.v = 1;
    v2.v = 2;
    v3.v = 3;
    v4.v = 4;
    v5.v = 5;

    LinkList_Insert(list, (LinkListNode *)&v1, LinkList_Length(list));
    LinkList_Insert(list, (LinkListNode *)&v2, LinkList_Length(list));
    LinkList_Insert(list, (LinkListNode *)&v3, LinkList_Length(list));
    LinkList_Insert(list, (LinkListNode *)&v4, LinkList_Length(list));
    LinkList_Insert(list, (LinkListNode *)&v5, LinkList_Length(list));

    for (i = 0; i < LinkList_Length(list); i++) {
        Value_t *pv = (Value_t *)LinkList_Get(list, i);
        fprintf(stdout, "%d\n", pv->v);
    }

    while (LinkList_Length(list) > 0) {
        Value_t *pv = (Value_t *)LinkList_Delete(list, 0);
        fprintf(stdout, "Delete: %d\n", pv->v);
    }

    LinkList_Destroy(list);

    fprintf(stdout, "hello world!\n");
    return 0;
}
