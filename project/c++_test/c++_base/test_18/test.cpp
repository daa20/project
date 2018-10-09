#include <iostream>


using namespace std;

class Interface1 {
    public:
        virtual void print(void) = 0;
        virtual int add(int i, int j) = 0;
};

class Interface2 {
    public:
        virtual int add(int i, int j) = 0;
        virtual int minus(int i, int j) = 0;
};

class child : public Interface1, public Interface2 {
    public:
        void print(void) 
        {
            cout << "child::print()" << endl;
        }

        int add(int i, int j)
        {
            return i + j;
        }

        int minus(int i, int j)
        {
            return i - j;
        }
};

void 
run(void)
{
    child c;
    c.print();

    cout << c.add(3, 5) << endl;
    cout << c.minus(4, 6) << endl;


    Interface1 *i1 = &c;
    Interface2 *i2 = &c;

    cout << i1->add(7, 8) << endl;
    i1->print();

    cout << i2->add(7, 8) << endl;
    cout << i2->minus(7, 8) << endl;
}

int
main(int argc, char *const argv[])
{

    run();

    cout << "Hello world" << endl;

    return 0;
}
