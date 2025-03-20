#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "lidar_specs.h"
#include "motion_specs.h"

void init_simulator();

extern double current_deg;
extern double current_x;
extern double current_y;

void move_by( const double c );
void turn_by( const double d );
void turn_to( const double d );
void move_to_exact( double x, double y, double deg );

extern double scan_pool[SCAN_LINES];

void scan();
void scan_at(double angle, double x, double y);

#endif