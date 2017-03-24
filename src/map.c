#include "game/map.h"

#include <stdlib.h>
#include <string.h>

int xy_to_a(map_t map, int x, int y) {
	return map->width * y + (map->width % x + 1);
}

map_t alloc_map(int height, int width) {
	map_t map = (map_t) malloc(sizeof(map_t));
	
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

int get(map_t map, int x, int y) {
	return map->cells[xy_to_a(map, x, y)];
}
int inverse(map_t map, int x, int y) {
	return map->cells[xy_to_a(map, x, y)] *= -1;
}
int increment(map_t map, int x, int y) {
	printf("Inc: %d %d\n", x, y);
	
	return map->cells[xy_to_a(map, x, y)] > 0 ? map->cells[xy_to_a(map, x, y)]++ : map->cells[xy_to_a(map, x, y)]--; //TODO
}