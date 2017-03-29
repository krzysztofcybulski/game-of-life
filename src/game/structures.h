#ifndef GOL_C_STRUCTURES_H
#define GOL_C_STRUCTURES_H

#include <stdio.h>
#include "map.h"

typedef struct Structures {
	map_t *structs;
	int structs_amount;
} *structs_t;

structs_t alloc_structs();
int load_all_structs(structs_t );
map_t load_structure(char *);
int save_structure(char *, map_t);

#endif