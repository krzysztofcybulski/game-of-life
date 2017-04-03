#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "utils/colors.h"

#include "game/game.h"
#include "game/rules.h"
#include "game/map.h"
#include "game/rules.h"
#include "test/test.h"
#include "game/game_cmds.h"
#include "parser/cmd.h"

rules_t load_test_rules();

void flags_handling(int argc, char ** args) {
	int c;

	while(1) {
		//map_t map = alloc_map("nowa_mapa", 0, 0);	

		static struct option long_option[] = {
			{"rules", required_argument,0, 'r'},
			{"height ", required_argument, 0, 'h'},
			{"width ", required_argument, 0, 'w'},
			{"config", required_argument, 0, 'c'}, 
			{0, 0, 0, 0}

		};
		int index = 0;
		c = getopt_long(argc, args, "c:h:w:s:", long_option, &index);

		if(c == -1) {
			break;
		}

		switch(c) {
			case 'c':
				//printf("option -c with value %s\n", optarg);
				break;
			case 'r':
				printf("option -r with value %s\n", optarg);
				//rules_t r = load_rules(optarg);
				break;
			case 'h':
				printf("option -h with value %s\n", optarg);
				//map->height = optarg;
				break;
			case 'w':
				printf("option -w with value %s\n", optarg);
				//map->width = optarg;
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
	
	map_t map = alloc_map("nowa_mapa", 20, 20);
	game_t game = start(r, map);
	
	int actives[] = {1, 22, 40, 41, 42};
	place(game, (int*)actives, 5);
	move(game, 1, 0, NULL);
	
    golsh_loop();

	free(game);
	return EXIT_SUCCESS;
}
