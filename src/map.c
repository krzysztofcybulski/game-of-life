#include "game/map.h"

#include <stdlib.h>
#include <string.h>

map_t alloc_map(char *name, int height, int width) {
	map_t map = (map_t) malloc(sizeof(struct Map));
//	char buffor[50];
	map->name = name; 
	map->height = height;
	map->width = width;
	
	int cells_size = height * width * sizeof(int);
	map->cells = malloc(cells_size);
	memset(map->cells, 0, cells_size);
	
	return map;
}


int invert(map_t map, int position) {
	if(map->cells[position] < SPLITTER)
		map->cells[position] += SPLITTER;
	else
		map->cells[position] -= SPLITTER;
	return map->cells[position];
}

int increment(map_t map, int position, int change) {
	int x = position % map->width;
	int y = position / map->width;
	
	if(x < 0 || x >= map->width || y < 0 || y >= map->height)
		return 0;
	
	if(map->cells[change] >= SPLITTER)
		return ++map->cells[position];
	else
		return --map->cells[position];
}