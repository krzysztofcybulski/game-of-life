#include "game/map.h"

#include <stdlib.h>
#include <string.h>

map_t alloc_map(int height, int width) {
	map_t map = (map_t) malloc(sizeof(struct Map));
	
	map->height = height;
	map->width = width;
	
	int cells_size = height * width * sizeof(int);
	map->cells = malloc(cells_size);
	memset(map->cells, 0, cells_size);
	
	return map;
}

int load_map(FILE* file) {
	return 0;
}

int invert(map_t map, int position) {
	if(map->cells[position] < SPLITTER)
		map->cells[position] += SPLITTER;
	else
		map->cells[position] -= SPLITTER;
	return map->cells[position];
}

int increment(map_t map, int position, int change) {	
	if(map->cells[change] >= SPLITTER)
		return ++map->cells[position];
	else
		return --map->cells[position];
}