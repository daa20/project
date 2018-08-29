#include <stdio.h>

void 
byte_order(void)
{
    typedef union _test_t{
        short value;
        char arr[sizeof(short)];
    } test_t;

    test_t test = {};
    
    test.value = 0x0102;

    if ((test.arr[0] == 0x01) && (test.arr[1] == 0x02)) {

        printf("big endian!\n");
    } else if ((test.arr[0] == 0x02) && (test.arr[1] == 0x01)) {

        printf("little endian!\n");
    } else {
        printf("unkown!\n");
    }

    printf("value: %d\n", test.value);
}

int
main(int argc, char *const argv[])
{

    byte_order();

    printf("hello world!\n");
    return 0;
}
