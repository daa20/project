#include <iostream>


using namespace std;


class Test {
    private:
        static int count;
    public:
        Test();
        static int getCount(void);
        ~Test();
};


int Test::count = 0;

Test::Test()
{
    count++;
}

int
Test::getCount(void) 
{
    return count;
}

Test::~Test()
{
    count--;
}


void 
test_1(void) 
{
    Test t1[100];

    cout << "Current count: " << Test::getCount() << endl;

}

void 
test_2(void)
{
    Test t1;
    Test t2;

    cout << "Current count: " << Test::getCount() << endl;
   
    test_1();

    cout << "Current count: " << Test::getCount() << endl;
}

int
main(int argc, char *const argv[])
{

    test_2();

    cout << "hello world" << endl;

    return 0;
}
