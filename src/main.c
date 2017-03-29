#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "utils/colors.h"

#include "game/game.h"
#include "game/rules.h"
#include "game/map.h"

#include "test/test.h"

#include "game/game_cmds.h"

void flags_handling(int argc, char ** args) {
	int c;

	while(1) {
		static struct option long_option[] = {
			{"rules", required_argument,0, 'r'},
			{"size ", required_argument, 0, 's'},
			{"config", required_argument, 0, 'c'}, 
			{0, 0, 0, 0}

		};
		int index = 0;
		c = getopt_long(argc, args, "c:r:s:", long_option, &index);

		if(c == -1) {
			break;
		}

		switch(c) {
			case 'c':
				printf("option -c with value %s\n",optarg );
				break;
			case 'r':
				printf("option -r with value %s\n",optarg );
				break;
			case 's':
				printf("option -s with value %s\n",optarg );
				break;	
			case '?':
				break;
			default:
				abort();
    }	
	}
}


int main(int argc, char **argv) {
	
	if(argc > 1 && strcmp(argv[1], "test") == 0) {
		utests_t utests = alloc_utests();
		return print_results(utests);
	}
 	flags_handling(argc, argv);

	
	/*TEST RULES*/
	rules_t r = (rules_t) malloc(sizeof(struct Rules));
	r->name = "test";
	int live[2] = {12, 13};
	r->live = (int*)live;
	r->live_n = 2;
	int born[1] = {3};
	r->born = (int*)born;
	r->born_n = 1;
	int neighbours[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	int (*ne)[2] = neighbours;
	r->neighbours_amount = 8;
	r->neighbours = ne;
	
	map_t map = alloc_map(20, 20);
	game_t game = start(r, map);
	
	int actives[] = {1, 22, 40, 41, 42};
	place(game, (int*)actives, 5);
	
	move(game, 80, 100000);
	free(game);
	
	return EXIT_SUCCESS;
}
