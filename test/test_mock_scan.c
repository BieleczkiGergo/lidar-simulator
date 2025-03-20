#include <stdio.h>
#include "lidar_specs.h"
#include "test_assets.h"
#include "simulator.h"
#include "reader.h"

int main()
{
    const double origin_deg = 60;
    const double origin_x = 12;
    const double origin_y = 3;

    // read_barrier_file("assets/maps/box.txt");
    read_barrier_file("assets/maps/top_slit.txt");
    print_barriers();
    scan_at( origin_deg, origin_x, origin_y );
    print_scan_pool( origin_deg, origin_x, origin_y );
    // print_scan_pool_with_index( origin_deg, origin_x, origin_y );
    putchar('\n');

    return 0;
}