#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "utils/colors.h"

#include "game/game.h"
#include "game/structures.h"
#include "game/rules.h"
#include "game/golsh.h"
#include "game/map.h"
#include "game/rules.h"
#include "test/test.h"
#include "game/game_cmds.h"
#include "parser/cmd.h"

rules_t load_test_rules();

game_t flags_handling(int argc, char ** args) {
	int c;
	
	int height = 20;
	int width = 20;
	map_t map = alloc_map("main", height, width);
	rules_t rules = load_rules("conway_moor");
	
	while(1) {
		static struct option long_option[] = {
			{"rules", required_argument, 0, 'r'},
			{"height ", required_argument, 0, 'h'},
			{"width ", required_argument, 0, 'w'},
			{"map", required_argument, 0, 'm'}, 
			{0, 0, 0, 0}

		};
		
		int index = 0;
		c = getopt_long(argc, args, "m:h:w:s:", long_option, &index);

		if(c == -1)
			break;

		switch(c) {
			case 'm':
				free(map);
				map = load_structure(optarg);
				break;
			case 'r':
				free(rules);
				rules = load_rules(optarg);
				break;
			case 'h':
				height = atoi(optarg);
				break;
			case 'w':
				width = atoi(optarg);
				break;		
			case '?':
				break;
			default:
				abort();
   		}
	}
	
	if(strcmp(map->name, "main") == 0) {
		free(map);
		map = alloc_map("main", height, width);
		printf("ELO! %s %d\n", rules->name, rules->born_n);
	}
	
	return start(rules, map);
}


int main(int argc, char **argv) {
	
	if(argc > 1 && strcmp(argv[1], "test") == 0) {
		utests_t utests = alloc_utests();
		return print_results(utests);
	}
 	
	game_t game = flags_handling(argc, argv);
	
	int actives[] = {1, 22, 40, 41, 42};
	place(game, (int*)actives, 5);
	move(game, 1, 0, NULL);

	printf("I: %d\n", game->actives_amount);
	
    golsh_loop(game);

	free(game);
	return EXIT_SUCCESS;
}
