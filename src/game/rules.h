#ifndef GOL_C_RULES_H
#define GOL_C_RULES_H

typedef struct Rules {
	char *name;
    int *live;
	int live_n;
	int *born;
	int born_n;
	int (*neighbours)[2];
	int neighbours_amount;
} *rules_t;

#endif