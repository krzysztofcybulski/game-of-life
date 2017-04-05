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

map_t load_map(char *name) {
	char path[50]= "resources/structures/";
	strcat(path, name);
	
	char map_name[50];
	int i = 0, w, h;
	FILE *in = fopen(path, "r");

	if(in == NULL) 
		printf("Problem with loading map file!");

	fscanf(in, "%s %d %d", map_name, &h, &w);

	map_t load = alloc_map(map_name, h, w);

	for(i = 0; i < load->height * load->width; i++)
		fscanf(in, "%d", &load->cells[i]);
			
	fclose(in);
	return load;

}

int save_map(char *name, map_t struc) {
	char path[50]="resources/structures/";
	strcat(path, name);
	FILE *out = fopen(path, "w");
	if(out == NULL ) {
		printf("Can't save map file");
		return -1;
	}
	fprintf(out, "%s %d %d\n",struc->name, struc->width, struc->height);
	int i;
	for(i=0; i< (struc->width * struc->height); i++)
		fprintf(out, "%d ", struc->cells[i]);

	fclose(out);

	return 1;
}