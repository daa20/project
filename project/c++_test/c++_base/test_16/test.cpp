#include <iostream>


using namespace std;


class parent {
    public:
        parent() 
        {
            this->func();
        }

        virtual void func(void) 
        {
            //cout << "parent::func()" << endl;
        }
};

class child : public parent {
    public:
        child() 
        {
            //this->func();
        }
        void func(void) 
        {
            cout << "child::func()" << endl;
        }
};

void
run(void) 
{
    child c;
    c.func();
}


int
main(int argc, char *const argv[])
{

    run();
    cout << "hello world" << endl;

    return 0;
}
