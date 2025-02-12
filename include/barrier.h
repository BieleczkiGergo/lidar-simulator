#ifndef BARRIER_H
#define BARRIER_H

typedef struct barrier {
    double pos;
    double start;
    double end;

} Barrier;

extern Barrier* vertical_barriers;
extern Barrier* horizontal_barriers;

extern int vertical_size;
extern int horizontal size;

#endif