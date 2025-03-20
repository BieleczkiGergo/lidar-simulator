#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include "barrier.h"
#include "test_assets.h"

unsigned int horizontal_lines;
unsigned int vertical_lines;

char lineBuf[MAX_LINE_LEN];

void alloc_barriers( unsigned int vertical, unsigned int horizontal )
{
    vertical_barriers = malloc( sizeof(Barrier) * vertical );
    vertical_size = vertical;

    horizontal_barriers = malloc( sizeof(Barrier) * horizontal );
    horizontal_size = horizontal;

}

void read_barrier_file( char* filename )
{
    FILE *fptr = fopen(filename, "r");
    

    int c = ' ';
    // 0: pos   1: start   2: end
    unsigned short positions[3] = { 0, 0, 0 };
    // which number it's urrently reading
    unsigned short reading = 0;
    // 0: was in a number   1: was in a space
    unsigned short num_state = 1;

    // read the first line of the file
    fgets(lineBuf, MAX_LINE_LEN, fptr);
    // read the first line
    unsigned short horizontal_lines;
    unsigned short vertical_lines;

    for(int i=0; '\n' != (c = lineBuf[i]); i++)
    {
        if( '0' <= c && '9' >= c )
        {
            if( 1 == num_state )
            {
                positions[reading] = i;
                reading++;
            }
            num_state = 0;

        } else
        {
            lineBuf[i] = '\0';
            num_state = 1;

        }

    }

    horizontal_lines = atoi(lineBuf + positions[0]);
    vertical_lines = atoi(lineBuf + positions[1]);

    alloc_barriers( vertical_lines, horizontal_lines );

    positions[0] = 0;
    positions[1] = 0;
    // positions[2] = 0;

    // read horizontal barriers
    for(    int barrier_index=0; 
            ( (horizontal_lines + vertical_lines) > barrier_index ) && ( NULL != fgets(lineBuf, MAX_LINE_LEN, fptr) );
            barrier_index++ )
    {
        int i = 0;
        c = lineBuf[0];
        num_state = 1;
        reading = 0;
        for(i=0; ('\n' != c) && ('\0' != c) ; c = lineBuf[ ++i ])
        {
            if( ' ' == c || '\t' == c )
            {
                lineBuf[i] = '\0';
                num_state = 1;

            } else if( ('0' <= c && '9' >= c) || '.' == c || ',' == c || '-' == c )
            {
                if( 1 == num_state )
                {
                    positions[ reading++ ] = i;

                }
                num_state = 0;
            }

        }

        c = lineBuf[i];
        lineBuf[i] = '\0';
        
        double pos = atof( lineBuf + positions[0] );
        double start = atof( lineBuf + positions[1] );
        double end = atof( lineBuf + positions[2] );

        if( end < start )
        {
            double temp = start;
            start = end;
            end = temp;

        }

        if( barrier_index < horizontal_lines ){
            horizontal_barriers[ barrier_index ].pos = pos;
            horizontal_barriers[ barrier_index ].start = start;
            horizontal_barriers[ barrier_index ].end = end;

        } else {
            const int index = barrier_index - horizontal_lines;
            vertical_barriers[ index ].pos = pos;
            vertical_barriers[ index ].start = start;
            vertical_barriers[ index ].end = end;

        }

    }

    fclose(fptr);

}