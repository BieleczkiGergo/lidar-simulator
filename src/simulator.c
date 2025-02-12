#include <math.h>
#include "simulator.h"
#include "barrier.h"
#include "lidar_specs.h"

#define deg_to_rad(DEG) (DEG * M_PI / 180)

double scan_pool[SCAN_LINES];

void scan()
{
    //TODO: implement movement
    scan_at(0, 0);

}

void scan_at(double x, double y)
{
    // binary search where lidar pos would be in barriers
    // horizontal barriers
    int vertical_pos = 0;
    int horizontal_pos = 0;
    int min = 0;
    int max = horizontal_size;
    while( 1 < max - min )
    {
        int mid = (max + min) / 2;
        if( horizontal_barriers[mid].pos < y )
            max = mid;

        else if ( horizontal_barriers[mid].pos < y )
            min = mid;

        else
        {
            horizontal_pos = mid;
            break;

        }

        if( 1 < max - min )
            horizontal_pos = mid;

    }

    // vertical barriers
    int min = 0;
    int max = vertical_size;
    while( 1 < max - min )
    {
        int mid = (max + min) / 2;
        if( vertical_barriers[mid].pos < y )
            max = mid;

        else if ( vertical_barriers[mid].pos < y )
            min = mid;

        else
        {
            vertical_pos = mid;
            break;

        }

        if( 1 < max - min )
            vertical_pos = mid;

    }

    // iterate through scan lines
    for(int i=0; i < SCAN_LINES; i++)
    {
        const double deg = i * 360 / SCAN_LINES;
        const double a = (double) (deg != 90 && deg != 270);
        const double m = (1 == a) ? sin( deg_to_rad(deg) ) : 1;
        const double b = a*y - m*x;

        double vertical_dist = 0;
        double horizontal_dist = 0;

        // scan for horizontal barriers
        if( 0 < deg && 180 > deg)
        {
            for(int j=horizontal_pos; j < horizontal_size || horizontal_dist != 0; j++)
            {
                double touch;
            }

        }

    }
}
