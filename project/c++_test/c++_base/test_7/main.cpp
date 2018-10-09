#include <iostream>

#include "array.h"
using namespace std;

void 
test_1(void)
{
    Array a1(10);

    cout << "a1 length: " << a1.length() << endl;

    for (int i = 0; i < 10; i++) {
        a1.setData(i, i + 1);
    }

    for (int i = 0; i < a1.length(); i++) {
        cout << i << "th : " << a1.getData(i) << endl;
    }

    Array a2 = a1;

    cout << "a2 length: " << a2.length() << endl;
    
    for (int i = 0; i < a2.length(); i++) {
        cout << i << "th : " << a2.getData(i) << endl;
    }

    //a2.destory(); //destructor to do.
    //a1.destory(); //destructor to do.
    
    cout << "a1 length: " << a1.length() << endl;
    cout << "a2 length: " << a2.length() << endl;
}


int 
main(int argc, char *const argv[])
{
    test_1();

    cout << "hello world" << endl;

    return 0;
}
