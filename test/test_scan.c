#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "test_assets.h"
#include "simulator.h"

int main()
{
    // initialize barriers
    alloc_barriers(3, 3);

    put_vertical_barrier( 0, 0, 3, -1 );
    put_vertical_barrier( 1, -3, 5, 2 );
    put_vertical_barrier( 2, 3, 20, 2.5 );

    put_horizontal_barrier( 0, -1, -1.5, -2 );
    put_horizontal_barrier( 1, -1, 4, 3 );
    put_horizontal_barrier( 2, -1, -1.5, -4 );

    scan();

    printf( "expected: %f ; actual: %f ; result: %d\n", 3.0, scan_pool[0], assert_double( 3.0, scan_pool[0] ) );

    return 0;
}