#include <iostream>
#include "base.h"
#include "sub.h"

using namespace std;

#if 1

/* enable polymorhism */
void 
test(Base &b)
{
    b.fn();
}

#else

/* disable polymorphism */
void
test(Base b)
{
    b.fn();
}

#endif

int
main(int argc, char *const argv[])
{

    Base    bc;
    Sub     sc;

    test(bc);

    test(sc);

    cout << "Hello world!" << endl;
    return 0;
}
