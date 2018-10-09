#include <iostream>
#include <stdexcept>

using namespace std;

class divide_by_zero : public logic_error {
    public:
        divide_by_zero(const char *s) : logic_error(s) {}
};

double
DIV(double a, double b)
{
    if ((b > -0.000001) && (b < 0.000001)) {
        throw divide_by_zero("Divide by zero...!");
    }
    return a / b;
}

void
run(void)
{
    try {
        cout << DIV(1, 2) << endl;
        cout << DIV(1, 0) << endl;
        cout << DIV(1, 4) << endl;
    } catch(exception &e) {
        cout << e.what() << endl;
    }
}

int
main(int argc, char *const argv[])
{
    run();

    cout << "Hello world" << endl;

    return 0;
}
