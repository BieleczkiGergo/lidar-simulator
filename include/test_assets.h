#ifndef TEST_ASSETS_H
#define TEST_ASSETS_H

#include "barrier.h"

#define EPSILON 0.0001
unsigned int assert_double( double expected, double actual );

void print_barriers();

void put_horizontal_barrier( unsigned int index, double start, double end, double pos );
void put_vertical_barrier( unsigned int index, double start, double end, double pos );

unsigned int assert_barrier( double start, double end, double pos, Barrier* barrier );

void print_scan_pool(double deg, double x, double y);

void print_pos_chain();

#endif