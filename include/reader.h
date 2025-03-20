#ifndef READER_H
#define READER_H

#include "barrier.h"

#define MAX_LINE_LEN 70

void alloc_barriers( unsigned int vertical, unsigned int horizontal );

void read_barrier_file( char* filename );

#endif