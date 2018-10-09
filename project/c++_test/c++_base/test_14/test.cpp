#include <iostream>


using namespace std;



class object {
    public:

        object(const char *s);
        ~object();

};


object::object(const char *s)
{
    cout << "object() " << s << endl;
}


object::~object()
{
    cout << "~object()" << endl;
}


class parent : public object {
    public:
        parent(const char *s);
        ~parent();
};

parent::parent(const char *s) : object(s)
{
    cout << "parent() " << s << endl;
}

parent::~parent()
{
    cout << "~parent()" << endl;
}

class child : public parent {
    protected:
        object o1;
        object o2;
    public:
        child();
        ~child();
};

child::child() : o2("o2"), o1("o1"), parent("parent")
{
    cout << "child()" << endl;
}

child::~child()
{
    cout << "~child()" << endl;
}


void 
test_1(void)
{
    child c1;
}


int 
main(int argc, char *const argv[])
{

    test_1();

    cout << "Hello world" << endl;

    return 0;
}
