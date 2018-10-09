#include <iostream>


using namespace std;

template <typename T1, typename T2>
class Test {
    public:
        void add(T1 a, T2 b)
        {
            cout << "add(T1, T2)" << endl;
            cout << a + b << endl;
        }
};

/*
template <typename T>
class Test<T, T> {
    public:
        void add(T a, T b) 
        {
            cout << "add(T, T)" << endl;
            cout << static_cast<T>(a + b) << endl;
        }
};
*/

template <typename T>
class Test <T, int> {
    public:
        void add(T a, int b)
        {
            cout << "add(T, int)" << endl;
            cout << a + b << endl;
        }
};

template <typename T1, typename T2>
class Test <T1*, T2*> {
    public:
        void add(T1* a, T2* b)
        {
            cout << "add(T1*, T2*)" << endl;
            cout << *a + *b << endl;
        }

};

void
run(void)
{

    int i = 1;
    int j = 2;
    
    Test<double, int> t;
    Test<long, long> ti;
    Test<float, int> tt;
    Test<int *, int *> tp;

    t.add(10.001, 8);

    ti.add(2, 3);

    tt.add(4, 5);

    tp.add(&i, &j);
}

int
main(int argc, char *const argv[])
{
    run();

    cout << "Hello world" << endl;

    return 0;
}
