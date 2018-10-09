#include <iostream>
#include <stdio.h>
#include "operator.h"

using namespace std;


void 
test_1(void)
{
    double r = 0;
    Operator op;
    op.setOperator('*');
    op.setParameter(4, 3);

    if (op.result(r)) {
        printf("result: %f\n", r);
    }

}

int 
main(int argc, char *const argv[])
{
    test_1();

    cout << "hello world" << endl;

    return 0;
}
