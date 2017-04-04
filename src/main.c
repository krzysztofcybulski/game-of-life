#include <stdio.h>
#include <string.h>

#include "test/test.h"

#include "parser/parser.h"
#include "parser/cmd_proxy.h"
#include "parser/commands.h"

#include "game/map.h"
#include "game/rules.h"
#include "game/game.h"

int main(int argc, char **argv) {
	
	/* Run tests */
	if(argc > 1 && strcmp(argv[1], "test") == 0) {
		utests_t utests = alloc_utests();
		return print_results(utests);
	}
 	
	/* Register all commands */
	parser_t parser = alloc_parser(12);
	register_all_cmds(parser);
	
	rules_t rules = load_rules("conway_moor");
	map_t map = alloc_map(20, 20);
	game_t game = start(rules, map);
    golsh_loop(game, parser);
  
	free(game);
	return EXIT_SUCCESS;
}