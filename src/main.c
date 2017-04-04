#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>



#include "test/test.h"

#include "parser/parser.h"
#include "parser/cmd_proxy.h"
#include "parser/commands.h"

#include "game/map.h"
#include "game/structures.h"
#include "game/rules.h"
#include "game/game.h"
#include "game/flags.h"

int main(int argc, char **argv) {
	
	/* Run tests */
	if(argc > 1 && strcmp(argv[1], "test") == 0) {
		utests_t utests = alloc_utests();
		return print_results(utests);
	}
 	
	/* Register all commands */
	parser_t parser = alloc_parser(12);
	register_all_cmds(parser);
	
	game_t game = flags_handling(argc, argv);

/*	rules_t rules = load_rules("conway_moor");
	map_t map = load_structure("spaceship");//alloc_map(20, 20);
	game_t game = start(rules, map);*/

	recalculate(game);
    golsh_loop(game, parser);
  
	free(game);
	return EXIT_SUCCESS;
}