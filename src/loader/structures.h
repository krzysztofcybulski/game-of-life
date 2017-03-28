#ifndef GOL_C_STRUCTURES_H
#define GOL_C_STRUCTURES_H

#include <../game/map.h>

typedef struct Structures() {
	char **names;
	map_t *structs;
	int structs_amount;
} *structs_t;

structs_t alloc_structs();
int load_all_structs(structs_t structs);
map_t load_structure(structs_t structs, char *name);
int save_structure(structs_t structs, char *name);

#endif