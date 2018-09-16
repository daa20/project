#include <stdio.h>

#include "DLinkList.h"

typedef struct _tag_Value_t {
    DLinkListNode   header;
    int             v;
} Value_t;

int
main(int argc, char *const argv[])
{
    int i = 0;
    DLinkList   *list = DLinkList_Create();

    Value_t v1;
    Value_t v2;
    Value_t v3;
    Value_t v4;
    Value_t v5;

    v1.v = 1;
    v2.v = 2;
    v3.v = 3;
    v4.v = 4;
    v5.v = 5;

    DLinkList_Insert(list, (DLinkListNode *)&v1, DLinkList_Length(list));
    DLinkList_Insert(list, (DLinkListNode *)&v2, DLinkList_Length(list));
    DLinkList_Insert(list, (DLinkListNode *)&v3, DLinkList_Length(list));
    DLinkList_Insert(list, (DLinkListNode *)&v4, DLinkList_Length(list));
    DLinkList_Insert(list, (DLinkListNode *)&v5, DLinkList_Length(list));

    fprintf(stdout, "All members:\n");
    for (i = 0; i < DLinkList_Length(list); i++) {
        Value_t *pv = (Value_t *)DLinkList_Get(list, i);
        fprintf(stdout, "%d\n", pv->v);
    }

    fprintf(stdout, "Delete last member!\n");
    DLinkList_Delete(list, DLinkList_Length(list) - 1);
    fprintf(stdout, "Delete first member!\n");
    DLinkList_Delete(list, 0);

    fprintf(stdout, "The remainder:\n");
    for (i = 0; i < DLinkList_Length(list); i++) {
        Value_t *pv = (Value_t *)DLinkList_Next(list);
        fprintf(stdout, "next: %d\n", pv->v);
    }
    
    DLinkList_Reset(list);
    DLinkList_Next(list);

    Value_t *pv = (Value_t *)DLinkList_Current(list);
    fprintf(stdout, "current: %d\n", pv->v);

    DLinkList_Prev(list);

    pv = (Value_t *)DLinkList_Prev(list);
    fprintf(stdout, "current: %d\n", pv->v);

    fprintf(stdout, "Length: %d\n", DLinkList_Length(list));

    DLinkList_Destroy(list);

    fprintf(stdout, "hello world!\n");
    return 0;
}
