#include <stdio.h>
#include <stdlib.h>
#include "barrier.h"
#include "test_assets.h"
#include "reader.h"

const int VERTICAL_SIZE = 2;
const int HORIZONTAL_SIZE = 2;

int main()
{
    alloc_barriers( VERTICAL_SIZE, HORIZONTAL_SIZE );

    printf("horizontal ptr: %p ; vertical ptr: %p\n", vertical_barriers, horizontal_barriers);

    print_barriers();

    vertical_barriers[0].start = 6.9;
    vertical_barriers[0].end = 420;
    vertical_barriers[0].pos = 0.4;

    vertical_barriers[1] = (Barrier)
    {
        .start = 7,
        .end = 8.1,
        .pos = 1
    };

    print_barriers();

    return 0;
}
