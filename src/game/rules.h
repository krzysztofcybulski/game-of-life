#ifndef GOL_C_RULES_H
#define GOL_C_RULES_H

typedef struct Rules {
	char *name;
    int *live;
	int live_n;
	int *born;
	int born_n;
	int (*neighbors)[2];
	int neighbors_amount;
} *rules_t;

#endif