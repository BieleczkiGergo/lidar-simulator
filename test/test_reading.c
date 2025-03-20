#include <stdio.h>
#include "reader.h"
#include "test_assets.h"

int main()
{
    read_barrier_file("assets/box.txt");

    printf("horizontal barriers: %d ; vertical barriers: %d\n", horizontal_size, vertical_size);
    print_barriers();

    return 0;
}