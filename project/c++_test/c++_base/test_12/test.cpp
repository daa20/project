#include <iostream>


using namespace std;

#if 1
class Test {
    public:
        Test(int i);
        Test(const Test &obj);
        ~Test();
};
#else
class Test {
    public:
        explicit Test(int i);
        explicit Test(const Test &obj);
        ~Test();
};
#endif

Test::Test(int i)
{
    cout << "Test(int)" << endl;
}

Test::Test(const Test &obj)
{
    cout << "Test(const Test &)" << endl;
}

Test::~Test()
{
    cout << "~Test()" << endl;
}


void 
test_1(void)
{
    Test t1(5);
    Test t2 = 5;
    Test t3 = Test(5);
}

int 
main(int argc, char *const argv[])
{

    test_1();

    cout << "Hello world" << endl;

    return 0;
}
