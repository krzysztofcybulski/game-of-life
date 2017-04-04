#include <stdio.h>
#include <stdlib.h>

#include "utils/welcome.h"

void show_welcome(char *name) {
	FILE *w_file = fopen("resources/welcome_pl", "r");
	
	char input[255];
	char *status;
	
	do {
		status = fgets(input, sizeof(input), w_file);
		printf("%s", input);
	} while (status);
	
	printf("\n");
}