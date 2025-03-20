#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "barrier.h"
#include "test_assets.h"
#include "lidar_specs.h"
#include "simulator.h"

// The barriers should be printed in the same order in which they appear in the
// file or in which they would appear in the file. Refer to the 
// [Mathematical model](plan/math_model.md#Barrier_files)
void print_barriers()
{
    printf("horizontal barriers: %d\n", horizontal_size);
    for(int i=0; i < horizontal_size; i++)
    {
        printf("pos: %f ; start: %f ; end: %f\n", 
            horizontal_barriers[i].pos,
            horizontal_barriers[i].start, 
            horizontal_barriers[i].end 
        );
    }
    
    printf("vertical barriers:%d\n", vertical_size);
    for(int i=0; i < vertical_size; i++)
    {
        printf("pos: %f ; start: %f ; end: %f\n", 
            vertical_barriers[i].pos,
            vertical_barriers[i].start, 
            vertical_barriers[i].end 
        );
    }
}

void put_horizontal_barrier( unsigned int index, double start, double end, double pos )
{
    vertical_barriers[index].start = start;
    vertical_barriers[index].end = end;
    vertical_barriers[index].pos = pos;

}

void put_vertical_barrier( unsigned int index, double start, double end, double pos )
{
    horizontal_barriers[index].start = start;
    horizontal_barriers[index].end = end;
    horizontal_barriers[index].pos = pos;
    
}

unsigned int assert_barrier( double start, double end, double pos, Barrier* barrier )
{
    // TODO: write this function (duh)
    return 1;
}

unsigned int assert_double( double expected, double actual )
{
    return fabs( expected - actual ) < EPSILON;
}

void print_scan_pool( double deg, double x, double y )
{
    printf("%.2f %.2f %.2f\n", deg, x, y);
    for(int i=0; i<SCAN_LINES; i++)
    {
        if( 0 == scan_pool[i])
            printf("\e[31m%.2f\e[0m ", scan_pool[i]);
        else
            printf("%.2f ", scan_pool[i]);

    }
}

void print_scan_pool_with_index( double deg, double x, double y )
{
    printf("%.2f %.2f %.2f\n", deg, x, y);
    for(int i=0; i<SCAN_LINES; i++)
    {
        if( 0 == scan_pool[i])
            printf("\e[31m%d: %.2f\e[0m\n", i, scan_pool[i]);
        else
            printf("%d: %.2f\n", i, scan_pool[i]);

    }
}

void print_pos_chain()
{
    printf("%.2f;%.2f ", current_x, current_y);
    
}