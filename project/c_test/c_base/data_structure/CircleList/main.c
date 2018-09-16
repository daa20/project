#include <stdio.h>

#include "CircleList.h"

typedef struct _Value_t {
    CircleListNode  header;
    int             v;
} Value_t;



int
main(int argc, char *const argv[])
{
    int i = 0;

    CircleList  *list = CircleList_Create();
    
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

    CircleList_Insert(list, (CircleListNode *)&v1, CircleList_Length(list));
    CircleList_Insert(list, (CircleListNode *)&v2, CircleList_Length(list));
    CircleList_Insert(list, (CircleListNode *)&v3, CircleList_Length(list));
    CircleList_Insert(list, (CircleListNode *)&v4, CircleList_Length(list));
    CircleList_Insert(list, (CircleListNode *)&v5, CircleList_Length(list));
    
    for (i = 0; i < 2 * CircleList_Length(list); i++) {
        Value_t *pv = (Value_t *)CircleList_Get(list, i);
        fprintf(stdout, "%d\n", pv->v);
    
    }
    

    while (CircleList_Length(list) > 0) {
        Value_t *pv = (Value_t *)CircleList_Delete(list, 0);
        fprintf(stdout, "Del: %d\n", pv->v);
    }

    fprintf(stdout, "Length: %d\n", CircleList_Length(list));
    
    CircleList_Insert(list, (CircleListNode *)&v1, CircleList_Length(list));
    CircleList_Insert(list, (CircleListNode *)&v2, CircleList_Length(list));
    CircleList_Insert(list, (CircleListNode *)&v3, CircleList_Length(list));
    CircleList_Insert(list, (CircleListNode *)&v4, CircleList_Length(list));
    CircleList_Insert(list, (CircleListNode *)&v5, CircleList_Length(list));
    

    for (i = 0; i < CircleList_Length(list); i++) {
        Value_t *pv = (Value_t *)CircleList_Next(list);
        printf("%d\n", pv->v);
    }

    CircleList_Reset(list);

    while (CircleList_Length(list) > 0) {
        Value_t *pv = NULL;

        for (i = 1; i < 3; i++) {
            CircleList_Next(list);
        }

        pv = (Value_t *)CircleList_Current(list);
        printf("Current: %d\n", pv->v);

        CircleList_DeleteNode(list, (CircleListNode *)pv);
    }

    CircleList_Destroy(list);

    fprintf(stdout, "Hello world!\n");

    return 0;
}
