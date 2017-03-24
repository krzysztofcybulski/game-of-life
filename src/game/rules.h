#ifndef GOL_C_RULES_H
#define GOL_C_RULES_H

typedef struct Rules {
	char *name;
    int *live;
	int *born;
	int **neighbors;
	int neighbors_amount;
} *rules_t;

#endif