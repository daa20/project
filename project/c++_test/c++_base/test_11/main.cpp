#include <iostream>
#include <cstdio>

#include "array.h"

using namespace std;


void 
test_1(void)
{
    Array a1(10);
    Array a2(0);
    Array a3(0);


    if (a1 != a2) {
        printf("a1 != a2\n");   
    }

    for (int i = 0; i < a1.length(); i++) {
        a1[i] = i + 1;
    }

    for (int i = 0; i < a1.length(); i++) {
        printf("a1[%d] = %d\n", i, a1[i]);
    }

    a3 = a2 = a1;

    if (a1 == a2) {
        printf("a1 == a2\n");
    }

    for (int i = 0; i < a3.length(); i++) {
        printf("a3[%d] = %d\n", i, a3[i]);
    }
}

int 
main(int argc, char *const argv[])
{

    test_1();


    cout << "Hello world" << endl;
    return 0;
}
