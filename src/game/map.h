#ifndef GOL_C_MAP_H
#define GOL_C_MAP_H

#include <stdio.h>
#include <stdlib.h>

#define SPLITTER 10

typedef struct Map {
    int width;
    int height;
    int *cells;
} *map_t;

map_t alloc_map(int, int);
int load_map(FILE*);

int invert(map_t, int);
int increment(map_t, int, int);

#endif