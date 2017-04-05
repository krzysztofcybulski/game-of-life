#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "game/rules.h"

rules_t load_rules(char  *name) {
	char path[128];
	char rules_name[128];
	int born_n, live_n, neighbours_amount;
	strcat(path, name);
	
	snprintf(path, 128, "resources/rules/%s", name);

	char buf[128];
	int i;
	FILE *in = fopen(path, "r");

	if(in == NULL) 
		printf("Can't open rules file!\n");
	
	fscanf(in, "%s %s", buf, rules_name);
	fscanf(in, "%s %d", buf, &live_n);
	fscanf(in, "%s %d", buf, &born_n);
	fscanf(in, "%s %d", buf, &neighbours_amount);
	rules_t rules = alloc_rules(rules_name, live_n, born_n, neighbours_amount);
		
	fscanf(in, "%s", buf);
	for(i = 0; i < live_n; i++)
		fscanf(in, "%d", &rules->live[i]);

	fscanf(in, "%s", buf);
	for(i = 0; i < born_n; i++)
		fscanf(in, "%d", &rules->born[i]);
	
	fscanf(in, "%s", buf);
	for (i = 0; i < neighbours_amount; i++)
		fscanf(in, "%d %d", &rules->neighbours[i][0], &rules->neighbours[i][1]);

	fclose(in);
	return rules;
}

rules_t alloc_rules(char *name, int live_n, int born_n, int neighbours_amount) {
	rules_t rules = (rules_t) malloc(sizeof(struct Rules));
	rules->name = malloc((strlen(name) +1 ) * sizeof(char));
	strcpy(rules->name, name);
	rules->live_n = live_n;
	rules->born_n = born_n;
	rules->live = malloc(live_n * sizeof(int));
	rules->born = malloc(born_n * sizeof(int));
	rules->neighbours_amount = neighbours_amount;
	rules->neighbours = malloc (neighbours_amount * sizeof(int *) + (neighbours_amount * (2 * sizeof(int))));
	return rules;
}