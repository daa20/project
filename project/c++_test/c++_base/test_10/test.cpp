#include <iostream>


using namespace std;

class Complex {
    private:
        int a;
        int b;
    public:
        Complex(int a = 0, int b = 0);
        Complex operator+(const Complex &c2);
        void print(void);
};

Complex::Complex(int a, int b)
{
    this->a = a;
    this->b = b;
}

Complex Complex::operator+(const Complex &c2)
{
    Complex ret(0, 0);
    ret.a = this->a + c2.a;
    ret.b = this->b + c2.b;
    return ret;
}

void Complex::print(void)
{
    cout << this->a << "+" << this-> b << "i" << endl;
}

void
test_1(void)
{
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3 = c1 + c2; // ==>> c3 = c1.operator+(c2);

    c1.print();
    c2.print();
    c3.print();
}

int 
main(int argc, char *const argv[])
{
    test_1();

    cout << "Hello world" << endl;

    return 0;
}
