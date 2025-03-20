#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "simulator.h"
#include "barrier.h"
#include "lidar_specs.h"
#include "motion_specs.h"

void init_simulator()
{
    srand((unsigned int) time(NULL) * getpid());

}

#define toRad(DEG) (DEG * M_PI / 180)
#define square(X) ((X) * (X))
#define dist(X, Y) sqrt( square(X) + square(Y) )

double scan_pool[SCAN_LINES];
double current_deg = 0;
double current_x = 0;
double current_y = 0;

int binary_search( double v, Barrier* barriers, int size )
{
    // The result of this search tells where the sacnner should look first
    // so if v is smaller than all values, it should return 0, not -1
    // and if v is greater than all values, it should return size-1 not size
    int min = 0;
    int max = size;
    int mid = 0;

    if( v < barriers[0].pos )
        return 0;

    if( v >= barriers[ size- 1 ].pos )
        return size;

    while( 1 < ( max - min ) )
    {
        mid = ceil((max + min) / 2);
        
        if( barriers[mid].pos == v )
        {
            return mid;

        }

        if( barriers[mid].pos < v )
        {
            min = mid;

        }else {
            max = mid;

        }

    }

    return mid;

}

void scan()
{
    scan_at(current_deg, current_x, current_y);

}

void scan_at(double angle, double x, double y)
{
    // binary search where lidar pos would be in barriers
    int vertical_pos = binary_search( x, vertical_barriers, vertical_size );
    int horizontal_pos = binary_search( y, horizontal_barriers, horizontal_size );

    printf("positions: vertical: %d ; horizontal: %d\n", vertical_pos, horizontal_pos);

    // iterate through scan lines
    for(int i=0; i < SCAN_LINES; i++)
    {
        const double deg = fmod((i * 360 / SCAN_LINES) + angle, 360);
        
        const double a = ( 90 == deg || 270 == deg ) ? 0 : 1;
        const double m = tan( toRad(deg) );
        const double b = a*y - m*x;

        // printf("a: %f ; m: %f ; b: %f\n", a, m, b);

        double horizontal_dist = 0;
        double vertical_dist = 0;

        // scan for horizontal barriers
        if( 0 < deg && 180 > deg) // If degrees are between 0 and 180 iterate upwards
        {
            for(int j=horizontal_pos; j < horizontal_size && horizontal_dist == 0; j++)
            {
                double touch = (0 == m) ? x : (( a*horizontal_barriers[j].pos ) - b)  / m;
                //       ^^ x coordinate of where the beam and the barrier would touch

                // If it's within bounds, it is the first touching point and thus the result
                // of the scan.
                if( touch >= horizontal_barriers[j].start && touch <= horizontal_barriers[j].end )
                    horizontal_dist = dist(touch - x, horizontal_barriers[j].pos - y);

            }

        } else if( 180 <= deg && 360 > deg) // If degrees are between 180 and 360 iterate downwards
        {
            for(int j=horizontal_pos-1; j >= 0 && horizontal_dist == 0; j--)
            {
                double touch = (0 == m) ? x : (( a*horizontal_barriers[j].pos ) - b)  / m;
                
                if( touch >= horizontal_barriers[j].start && touch <= horizontal_barriers[j].end )
                    horizontal_dist = dist(touch - x, horizontal_barriers[j].pos - y);

            }

        } // if degrees are either 0 or 180, it doesn't touch any vertical barriers and the distance
        // stays at 0, indicating exactly this

        // scan for vertical barriers
        if( ( 0 <= deg && 90 > deg ) || ( 270 < deg && 360 > deg )  ) // iterate upwards
        {
            for(int j=vertical_pos; j < vertical_size && vertical_dist == 0; j++)
            {
                double touch = (a == 0)? y : ((m*vertical_barriers[j].pos) + b); // y coordinate of where the beam and the barrier would touch

                if( touch >= vertical_barriers[j].start && touch <= vertical_barriers[j].end )
                    vertical_dist = dist(touch - y, vertical_barriers[j].pos - x);

            }
        } else if( ( 90 < deg && 270 > deg) ) // iterate downwards
        {
            for(int j=vertical_pos-1; j >= 0 && vertical_dist == 0; j--)
            {
                double touch = (a == 0)? y : ((m*vertical_barriers[j].pos) + b);

                if( touch >= vertical_barriers[j].start && touch <= vertical_barriers[j].end )
                    vertical_dist = dist(touch - y, vertical_barriers[j].pos - x);

            }
        }

        // determine which is closer
        if( horizontal_dist == 0 )
        {
            scan_pool[i] = vertical_dist;

        }else if( vertical_dist == 0 )
        {
            scan_pool[i] = horizontal_dist;

        }else
        {
            scan_pool[i] = (horizontal_dist < vertical_dist) ? horizontal_dist : vertical_dist;

        }

    }
}

// code for moving should be based on tank movement
void move_by( double c )
{
    const double a = cos( toRad(current_deg) ) * c;
    const double b = sin( toRad(current_deg) ) * c;

    const double u_x = (((double) rand() / RAND_MAX) * ((double) uncertainty_x * 2 )) - uncertainty_x;
    const double u_y = (((double) rand() / RAND_MAX) * ((double) uncertainty_y * 2 )) - uncertainty_y;

    current_x += a + ( u_x * c );
    current_y += b + ( u_y * c );

}

void turn_by( double d )
{
    current_deg += d;

}

void move_to_exact( double x, double y, double deg )
{
    current_x = x;
    current_y = y;
    current_deg = deg;

}