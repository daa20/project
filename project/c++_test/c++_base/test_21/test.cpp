#include <iostream>


using namespace std;

template <typename T>
void
isPtr(T *a)
{
    cout << "is pointer" << endl;
}

void 
isPtr(...)
{
    cout << "is not pointer" << endl;
}

void
test_1(void)
{
    int *pi = NULL;
    isPtr(pi);

    float *pf = NULL;
    isPtr(pf);

    int i = 1;
    isPtr(i);

}

int
main(int argc, char *const argv[])
{

    test_1();


    cout << "Hello world" << endl;

    return 0;
}

