#include <iostream>


using namespace std;


class parent {
    public:
        void print(void) 
        {
            cout << "I am parent" << endl;
        }
};

class child : public parent {

    public:
        void print(void) 
        {
            cout << "I am child" << endl;
        }
};

void 
run_1(void)
{
    child c;

    c.print();

    c.parent::print();
}

void 
run_2(void)
{
    child c;
    parent *pp = &c;
    parent &rp = c;

    c.print();

    pp->print();

    rp.print();
}

int 
main(int argc, char *const argv[])
{
    cout << "----------" << endl;
    run_1();

    cout << "----------" << endl;
    run_2();
    
    cout << "----------" << endl;
    cout << "Hello world" << endl;

    return 0;
}
