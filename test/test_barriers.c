#include <stdio.h>
#include <stdlib.h>
#include "barrier.h"

const int VERTICAL_SIZE = 2;
const int HORIZONTAL_SIZE = 2;

void print_barriers()
{
    puts("horizontal barriers:");
    for(int i=0; i < HORIZONTAL_SIZE; i++)
    {
        printf("start: %f ; end: %f ; pos: %f\n", 
            horizontal_barriers[i].start, 
            horizontal_barriers[i].end, 
            horizontal_barriers[i].pos
        );
    }
    
    puts("vertical barriers:");
    for(int i=0; i < VERTICAL_SIZE; i++)
    {
        printf("start: %f ; end: %f ; pos: %f\n", 
            vertical_barriers[i].start, 
            vertical_barriers[i].end, 
            vertical_barriers[i].pos
        );
    }
}

int main()
{
    horizontal_barriers = malloc( HORIZONTAL_SIZE * sizeof(Barrier) );
    vertical_barriers = malloc( VERTICAL_SIZE * sizeof(Barrier) );

    printf("horizontal ptr: %p ; vertical ptr: %p\n", vertical_barriers, horizontal_barriers);

    print_barriers();

    vertical_barriers[0].pos = 0.4;
    vertical_barriers[0].start = 6.9;
    vertical_barriers[0].end = 420;

    print_barriers();

    return 0;
}
