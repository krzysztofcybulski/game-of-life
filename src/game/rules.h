#ifndef GOL_C_RULES_H
#define GOL_C_RULES_H

#include <stdio.h>

typedef struct Rules {
	char *name;
    int *live;
	int live_n;
	int *born;
	int born_n;
	int (*neighbours)[2];
	int neighbours_amount;
} *rules_t;

rules_t alloc_rules(char *name, int live_n, int born_n, int neighbours_amount);
rules_t load_rules(char  *name);

#endif