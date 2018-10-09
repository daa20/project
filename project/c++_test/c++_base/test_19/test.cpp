#include <iostream>


using namespace std;

int 
Max(int a, int b)
{
    cout << "Max(int, int)" << endl;
    return (a > b)? (a) : (b);
}


template <typename T>
T Max(T a, T b)
{
    cout << "Max(T, T)" << endl;
    return (a > b) ? (a) : (b);
}

template <typename T>
T Max(T a, T b, T c)
{
    cout << "Max(T, T, T)" << endl;
    return Max(Max(a, b), c);
}

template <typename RT, typename T1, typename T2>
RT Add(T1 a, T2 b)
{
    return static_cast<RT>(a + b);
}


void
test_1(void)
{

    int a = 1;
    int b = 3;

    cout << Max(a, b) << endl;

    cout << Max<>(a, b) << endl;

    float fa = 3.0;
    float fb = 4.0;

    cout << Max<float>(fa, fb) << endl;

    char ca = 6;
    char cb = 7;
    char cc = 8;

    cout << Max(ca, cb, cc) << endl;
}


void 
test_2(void)
{
    cout << Add<double>('a', 100) << endl;

    cout << Add<double>(10, 100) << endl;
}

int
main(int argc, char *const argv[])
{
    cout << "---------------" << endl;
    test_1();

    cout << "---------------" << endl;
    test_2();

    cout << "Hello world" << endl;

    return 0;
}
