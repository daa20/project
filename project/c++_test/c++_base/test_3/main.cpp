#include <iostream>

using namespace std;


void
test_1(void)
{
    int *p = new int;

    *p = 10;

    cout << "*p = " << *p << endl;

    delete p;
}

void 
test_2(void)
{
    int *p = new int[10];

    for (int i = 0; i < 10; i++) {
        p[i] = i + 1;
    }

    for (int i = 0; i < 10; i++) {
        cout << "p[" << i << "] = " << p[i] << ", ";
    }

    cout << endl;

    delete [] p;
}

void
test_3(void)
{
    int *p = new int(3);

    cout << "*p = " << *p << endl;

    delete p;
}

int
main(int argc, char *const argv[])
{

    test_1();
    
    test_2();

    test_3();

    cout << "hello world" << endl;
    return 0;
}
