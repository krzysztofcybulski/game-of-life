#ifndef GOL_C_RULES_H
#define GOL_C_RULES_H

typedef struct AllRules {
	rules_t *rules;
	int rules_amount;
} *all_rules_t;

typedef struct Rules {
	char *name;
    int *live;
	int live_n;
	int *born;
	int born_n;
	int (*neighbours)[2];
	int neighbours_amount;
} *rules_t;

all_rules_t alloc_all_rules();
int load_all_rules(all_rules_t all_rules);
rules_t load_rules(FILE *file);

#endif