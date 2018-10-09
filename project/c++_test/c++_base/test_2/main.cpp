#include <iostream>
#include <stdio.h>

using namespace std;

void
test_1(void)
{
    const int& a = 4;

    int     *p = (int *)&a;

    *p = 5;

    cout << a << endl;
}

#if 0
int &
f(void)
{
    static int a = 0;
    return a;
}

int &
g(void)
{
    int a = 0;
    return a;
}

void test_2(void)
{
    int a = f();
    int &b = g();

    f() = 10;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "f() = " << f() << endl;
}
#endif

typedef int (*PF) (int, int);
typedef int (&AF) (int, int);

int
ff(int a, int b)
{
    return ( a + b);
}

void
test_3(void)
{
    PF func1 = ff;
    cout << "func1(1, 2) = " << func1(1, 2) << endl;

    printf("&func1 = %p, &ff = %p\n", func1, ff);

    AF func2 = ff;
    cout << "func2(1, 2) = " << func2(1, 2) << endl;

    printf("&func2 = %p, &ff = %p\n", func2, ff);

}

int mul(int x = 1);
int 
mul(int x)
{
    return (x * x);
}

void 
test_4(void)
{
    cout << "mul(2) = " << mul() << endl;
}

int
main(int argc, char *const argv[])
{
 
    test_1();

    //test_2();

    test_3();

    test_4();

    cout << "Hello world\n" << endl;
    return 0;
}
