#include <stdio.h>

#define offset(TYPE, MEMBER)  (size_t)(&((TYPE *)0)->MEMBER)
/*
说明：获得结构体(TYPE)的变量成员(MEMBER)在此结构体中的偏移量。
(01)  ( (TYPE *)0 )              将零转型为TYPE类型指针，即TYPE类型的指针的地址是0。
(02)  ((TYPE *)0)->MEMBER        访问结构中的数据成员。
(03)  &( ( (TYPE *)0 )->MEMBER ) 取出数据成员的地址。由于TYPE的地址是0，这里获取到的地址就是相对MEMBER在TYPE中的偏移。
(04)  (size_t)(&(((TYPE*)0)->MEMBER)) 结果转换类型。
对于32位系统而言，size_t是unsigned int类型；对于64位系统而言，size_t是unsigned long类型。
 * */

#define container(ptr, type, member) ({                 \
    const typeof(((type *)0)->member) *__mptr = (ptr);  \
    (type *)((char *)__mptr - offset(type, member));})
/*
说明：根据"结构体(type)变量"中的"域成员变量(member)的指针(ptr)"来获取指向整个结构体变量的指针。
(01) typeof( ( (type *)0)->member )     取出member成员的变量类型。
(02) const typeof( ((type *)0)->member ) *__mptr = (ptr)    定义变量__mptr指针，并将ptr赋值给__mptr。经过这一步，__mptr为member数据类型的常量指针，其指向ptr所指向的地址。
(04) (char *)__mptr    将__mptr转换为字节型指针。
(05) offsetof(type,member))    就是获取"member成员"在"结构体type"中的位置偏移。
(06) (char *)__mptr - offsetof(type,member))    就是用来获取"结构体type"的指针的起始地址（为char *型指针）。
(07) (type *)( (char *)__mptr - offsetof(type,member) )    就是将"char *类型的结构体type的指针"转换为"type *类型的结构体type的指针"。 
 * */

typedef struct _test_t {
    int i;
    char c;
    float f;
    double d;
} test_t;

void
test_space(void)
{
    size_t i_addr = 0;
    size_t c_addr = 0;
    size_t f_addr = 0;
    size_t d_addr = 0;

    i_addr = offset(test_t, i);

    c_addr = offset(test_t, c);

    f_addr = offset(test_t, f);
    
    d_addr = offset(test_t, d);

    fprintf(stdout, "int: %ld\n"
                    "char: %ld\n"
                    "float: %ld\n"
                    "double: %ld\n",
                    sizeof(int), sizeof(char), sizeof(float), sizeof(double));

    fprintf(stdout, "i_addr = %ld\n", i_addr);

    fprintf(stdout, "c_addr = %ld\n", c_addr);

    fprintf(stdout, "f_addr = %ld\n", f_addr);

    fprintf(stdout, "d_addr = %ld\n", d_addr);
}

void
test_assign(void)
{
    test_t t1 = {};
    test_t *t2;

    t1.i = 1;
    t1.c = 'a';
    t1.f = 1.2;
    t1.d = 2.4;

    t2 = container(&t1.i, test_t, i);

    printf("t2->i = %d\n", t2->i);
    printf("t2->c = %c\n", t2->c);
    printf("t2->f = %f\n", t2->f);
    printf("t2->d = %f\n", t2->d);

}

int
main(int argc, char *const argv[])
{
    test_space();

    test_assign();

    printf("hello world!\n");
    return 0;
}
