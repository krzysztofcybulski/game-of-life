#include "game/map.h"

#include <stdlib.h>
#include <string.h>

map_t alloc_map(char *name, int height, int width) {
	int i;
	
	map_t map = (map_t) malloc(sizeof(struct Map));
	map->name = malloc((strlen(name) + 1) * sizeof(char));
	strcpy(map->name, name);
	map->height = height;
	map->width = width;
	map->cells = malloc(height * width * sizeof(int));
	
	/*Zero map, we couldn't use memset*/
	for(i = 0; i < height * width; i++)
		map->cells[i] = 0;
	
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