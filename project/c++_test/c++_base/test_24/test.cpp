#include <iostream>
#include <typeinfo>

using namespace std;


class Parent {
    public:
        virtual ~Parent() {}
};


class Child : public Parent {
    public:
        int add(int a, int b) 
        {
            return a + b;
        }
};

class NewChild : public Parent {

};


#if 0
void
test(Parent *p)
{
    Child *c = dynamic_cast<Child *>(p);

    if (c != NULL) {
        cout << "Child" << endl;
        cout << c->add(10, 2) << endl;
    } else {
        
        if (dynamic_cast<NewChild *>(p) != NULL) {
            cout << "NewChild" << endl;
        } else {
            cout << "Parent" << endl;
        }
    
    }
}

#else

void
test(Parent *p)
{
    if (typeid(*p) == typeid(NewChild)) {
        cout << "NewChild" << endl;
    } else if (typeid(*p) == typeid(Child)) {
        cout << "Child" << endl;
    } else if (typeid(*p) == typeid(Parent)) {
        cout << "Parent" << endl;
    }
}

#endif

void
run(void)
{
    Parent parent;
    Child  child;
    NewChild nc;

    test(&parent);

    test(&child);

    test(&nc);
}

void 
run_1(void) 
{
    int             i = 0;
    char            c = 1;
    short           s = 2;
    unsigned int    ui = 3;
    float           f = 1.0;
    double          d = 2.0;
    

    if (typeid(i) == typeid(int)) {
        cout << "int" << endl;
    }

    if (typeid(c) == typeid(char)) {
        cout << "char" << endl;
    }

    if (typeid(s) == typeid(short)) {
        cout << "short" << endl;
    }

    if (typeid(ui) == typeid(unsigned int)) {
        cout << "unsigned int" << endl;
    }

    if (typeid(f) == typeid(float)) {
        cout << "float" << endl;
    }

    if (typeid(d) == typeid(double)) {
        cout << "double" << endl;
    }
}


int
main(int argc, char *const argv[])
{
    cout << "-----------------" << endl;
    run();

    cout << "-----------------" << endl;
    run_1();

    cout << "-----------------" << endl;
    cout << "Hello world" << endl;

    return 0;
}
