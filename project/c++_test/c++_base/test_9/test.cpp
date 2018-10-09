#include <iostream>
#include <cstdio>

using namespace std;


class Complex {
    private:
        int a;
        int b;
    public:
        Complex(int a = 0, int b = 0);
        int getA(void);
        int getB(void);
        friend Complex operator+(const Complex &c1, const Complex &c2);
        friend ostream& operator<<(ostream &out, const Complex &c);
};

Complex::Complex(int a, int b)
{
    this->a = a;
    this->b = b;
}

int 
Complex::getA(void)
{
    return this->a;
}

int 
Complex::getB(void)
{
    return this->b;
}

Complex operator+(const Complex &c1, const Complex &c2)
{
    Complex ret(0, 0);
    ret.a = c1.a + c2.a;
    ret.b = c1.b + c2.b;
    return ret;
}

ostream& operator<<(ostream &out, const Complex &c)
{
    out << c.a << "+" << c.b << "i";
    return out;
}


void 
test_1(void)
{
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3 = c1 + c2;

    cout << c1 << endl;
    cout << c2 << endl;
    cout << c3 << endl;
}

int
main(int argc, char *const argv[])
{

    test_1();

    printf("Hello world!\n");
    return 0;
}
