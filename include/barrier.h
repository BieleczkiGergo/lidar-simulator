#ifndef BARRIER_H
#define BARRIER_H

typedef struct barrier {
    double start;
    double end;
    double pos;

} Barrier;

extern Barrier* vertical_barriers;
extern Barrier* horizontal_barriers;

extern int vertical_size;
extern int horizontal_size;

#endif