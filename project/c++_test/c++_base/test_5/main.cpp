#include <iostream>
#include <stdio.h>

using namespace std;


void
test_1(void)
{
    const int x = 1;

    int &rx = const_cast<int &>(x);

    rx = 5;
    printf("x = %d, rx = %d, &x = %p, &rx = %p\n", x, rx, &x, &rx);


    volatile const int y = 2;

    int *p = NULL;

    p = const_cast<int *>(&y);

    *p = 6;

    printf("y = %d, *p = %d\n", y, *p);

    const int z = y; //have a influence for volatile

    p = const_cast<int *>(&z);

    *p = 7;

    printf("y = %d, z = %d, *p = %d\n", y, z, *p);

}

void 
test_2(void)
{
    char c = 'c';
    char &rc = c;
    const int &trc = c; //c = a, rc = a, trc = c
    //const char &trc = c;  //c = a, rc = a, trc = a
    rc = 'a';

    printf("c = %c, rc = %c, trc = %c\n", c, rc, trc);
}





int
main(int argc, char *const argv[])
{
    test_1();

    test_2();

    cout << "Hello world" << endl;

    return 0;
}
