#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct _person_t {
    int     age;
    char    name[20];
    struct  list_head list;
} person_t;

#define PERSON_MAX_COUNTS   (5)

int
main(int argc, char *const argv[])
{
    person_t            person_head;
    person_t            *pperson;
    struct list_head    *pos, *next;
    int                 i = 0;

    //初始化双链表的表头
    INIT_LIST_HEAD(&person_head.list);

    //添加节点
    for (i = 0; i < PERSON_MAX_COUNTS; i++) {
        pperson = (person_t *) malloc(sizeof(person_t));
        pperson->age = (i + 1) * 10;
        sprintf(pperson->name, "%4d", i + 1);

        //将节点链接到链表的末尾
        //如果想把节点链接到链表的表头后面，则使用list_add
        list_add_tail(&(pperson->list), &person_head.list);
    }

    //遍历节点
    printf("===list iterator d-link===\n");
    list_for_each(pos, &person_head.list) {
        pperson = list_entry(pos, person_t, list);
        fprintf(stdout, "name: %-2s, age: %d\n",
                pperson->name, pperson->age);
    }

    //删除节点age为20的节点
    printf("===delete node(age: 20)===\n");
    list_for_each_safe(pos, next, &person_head.list) {
        pperson = list_entry(pos, person_t, list);
        if (pperson->age == 20) {
            list_del_init(pos);
            free(pperson);
        }
    }

    //再次遍历链表
    printf("===2nd iterator d-link===\n");
    list_for_each(pos, &person_head.list) {
        pperson = list_entry(pos, person_t, list);
        fprintf(stdout, "name: %-2s, age: %d\n",
                pperson->name, pperson->age);
    }

    //释放资源
    list_for_each_safe(pos, next, &person_head.list){
        pperson = list_entry(pos, person_t, list);
        list_del_init(pos);
        free(pperson);
    }

    fprintf(stdout, "hello world!\n");
    return 0;
}
