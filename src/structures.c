#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "game/map.h"
#include "game/structures.h"


structs_t alloc_structs() {
	structs_t structures = (structs_t)malloc(sizeof(struct Structures));
	structures->structs = NULL;
	structures->structs_amount = 0;

	return structures;
}

map_t load_structure(char *name) {
	char path[50]= "resources/structures/";
	strcat(path, name);
	
	char map_name[50];
	int i = 0, w, h;
	FILE *in = fopen(path, "r");

	if(in == NULL) 
		printf("Problem with loading structure file!");

	fscanf(in, "%s %d %d", map_name, &h, &w);

	map_t load = alloc_map(map_name, h, w);

	for(i = 0; i < load->height * load->width; i++)
		if(fscanf(in, "%d", &load->cells[i])==1)

	/*The most important instruction*/
	load->cells[5];
			
	fclose(in);
	return load;

}

int load_all_structs(structs_t structs) {
	struct dirent *file;
	DIR * path;

	if((path = opendir(("resources/structures/"))) != NULL) {
		while((file = readdir(path)) != NULL) {
			structs = alloc_structs();
			structs->structs[structs->structs_amount] = load_structure(file->d_name);
			structs->structs_amount++;
		}
		closedir(path);
	} else {
		printf("Can't open structures dir");
		return 0;
	} 
	
	return 1;
}

int save_structure(char *name, map_t struc) {
	char path[50]="resources/structures/";
	strcat(path, name);
	FILE *out = fopen(path, "w");
	if(out == NULL ) {
		printf("Can't save structure file");
		return -1;
	}
	fprintf(out, "%s %d %d\n",struc->name, struc->width, struc->height);
	int i;
	for(i=0; i< (struc->width * struc->height); i++)
		fprintf(out, "%d ", struc->cells[i]);

	fclose(out);

	return 1;
}