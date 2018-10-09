#include <iostream>


using namespace std;


class Singleton {
    private:
        static Singleton *cInstance;
        Singleton() {}
    public:
        static Singleton *getInstance(void);
        void print(void);
};


Singleton* Singleton::cInstance = NULL;

Singleton* 
Singleton::getInstance(void)
{
    if (cInstance == NULL) {
        cout << "new Singleton()" << endl;
        cInstance = new Singleton();
    }

    return cInstance;
}

void 
Singleton::print(void)
{
    cout << "I am Singleton" << endl;
}


void
func(void)
{
    Singleton *s = Singleton::getInstance();
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();
    Singleton *s3 = Singleton::getInstance();

    cout << s << "    " << s1 << "    " << s2 << "    " << s3 << endl;

    s->print();
}

int
main(int argc, char *const argv[])
{
    func();

    cout << "Hello world" << endl;

    return 0;
}
