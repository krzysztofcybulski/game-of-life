#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "game/rules.h"

rules_t alloc_rules(char *name, int live_n, int born_n, int neighbours_amount) {
	rules_t rules = (rules_t) malloc(sizeof(struct Rules));
	rules->name = name;
	rules->live_n = live_n;
	rules->born_n = born_n;
	rules->live = malloc(live_n * sizeof(*rules->live));
	rules->born = malloc(born_n * sizeof(*rules->born));
	rules->neighbours_amount = neighbours_amount;	
	rules->neighbours = malloc(neighbours_amount * 2 * sizeof(int));
	//lub 	rules->neighbours = malloc(neighbours_amount * sizeof(*rules->neighbours));

	return rules;
}

all_rules_t alloc_all_rules() {
	all_rules_t all_rules = (all_rules_t)malloc(sizeof(struct AllRules));
	all_rules->rules = NULL;
	all_rules->rules_amount = 0;

	return all_rules;
}
rules_t load_rules(char  *name) {
	char path[50]="resources/rules/";
	char rules_name[50];
	int born_n, live_n, neighbours_amount;
	strcat(path, name);
	char buf[50];
	int i;
	FILE *in = fopen(path, "r");

	if(in == NULL) 
		printf("blad otwarcia pliku load_rules!");

	fscanf(in, "%s %s", buf, rules_name);
	fscanf(in, "%s %d", buf, &live_n);
	fscanf(in, "%s %d", buf, &born_n);
	fscanf(in, "%s %d", buf, &neighbours_amount);

	int neighbours[neighbours_amount][2]; 
	rules_t rules = alloc_rules(rules_name, live_n, born_n, neighbours_amount);
		
	fscanf(in, "%s", buf);
	for(i = 0; i < live_n; i++)
		fscanf(in, "%d", &rules->live[i]);

	fscanf(in, "%s", buf);
	for(i = 0; i < born_n; i++)
		fscanf(in, "%d", &rules->born[i]);


	fscanf(in, "%s", buf);
	for (i = 0; i < neighbours_amount; i++)
		fscanf(in, "%d %d", &neighbours[i][0], &neighbours[i][1]);
	
	int (*ne)[2] = neighbours;
	rules->neighbours = ne;

	fclose(in);

	return rules;


}
int load_all_rules(all_rules_t all_rules) {
	struct dirent *file;
	DIR *path;
	if((path = opendir(("resources/rules/"))) != NULL) {
		while((file = readdir(path)) != NULL) {
			all_rules = alloc_all_rules();
			all_rules->rules[all_rules->rules_amount] = load_rules(file->d_name);
			all_rules->rules_amount++;
		}

		closedir(path);
	} else {
		printf("blad przy load_all_rules!");
		return 0;
	} 
	return 1;


}
