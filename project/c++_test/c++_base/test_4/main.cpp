#include <stdio.h>

namespace First {
    int i = 1;
}

namespace Second {
    int i = 2;

    namespace Internal {
    
        struct P {
            int x;
            int y;
        };
    }
}


void 
test_1(void)
{
    using namespace First; // use all of First
    using Second::Internal::P;

    int i = 0;

    printf("First::i = %d\n", First::i);

    printf("Second::i = %d\n", Second::i);

    printf("i = %d\n", i);

    P p = {3, 4};

    printf("p.x = %d\n", p.x);
    printf("p.y = %d\n", p.y);
}


int
main(int argc, char *const argv[])
{

    test_1();


    return 0;
}

