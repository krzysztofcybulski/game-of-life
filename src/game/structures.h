#ifndef GOL_C_STRUCTURES_H
#define GOL_C_STRUCTURES_H

#include <stdio.h>
#include <map.h>

typedef struct Structures {
	map_t *structs;
	int structs_amount;
} *structs_t;

structs_t alloc_structs();
int load_all_structs(structs_t structs);
map_t load_structure(FILE *file);
int save_structure(structs_t structs, char *name, map_t struct);

#endif