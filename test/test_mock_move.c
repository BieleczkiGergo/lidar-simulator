#include <stdio.h>
#include "lidar_specs.h"
#include "test_assets.h"
#include "simulator.h"

int main()
{
    init_simulator();

    const double start_x = 0;
    const double start_y = 0;
    const double start_deg = 60;

    move_to_exact( start_x, start_y, start_deg );
    print_pos_chain();

    move_by(10);
    print_pos_chain();

    turn_by(-60);
    move_by(4);
    print_pos_chain();

    turn_by(90);
    move_by(7);
    print_pos_chain();

    printf("\n");

    return 0;
}