#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "lidar_specs.h"

extern double scan_pool[SCAN_LINES];

void scan();
void scan_at(double x, double y);

#endif