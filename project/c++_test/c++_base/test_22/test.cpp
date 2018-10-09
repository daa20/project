#include <iostream>


using namespace std;


#define DIV_ZERO_ERROR (-1)

double
DIV(double a, double b)
{
    if ((-0.000001 < b) && (b < 0.000001)) {
        throw DIV_ZERO_ERROR;
    } else {
        return a / b; 
    }
    
}

void 
run(void)
{
    try {

        cout << DIV(1, 3) << endl;

        cout << DIV(3, 0) << endl;

    } catch (int error) {

        if (error == DIV_ZERO_ERROR) {
            cout << "ZERO error!" << endl;
        } else {
            cout << "Other error!" << endl;
        }
    }
}

int
main(int argc, char *const argv[])
{
    run();

    cout << "Hello world" << endl;

    return 0;
}
