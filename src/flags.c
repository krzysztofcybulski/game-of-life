#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "parser/parser.h"
#include "parser/cmd_proxy.h"
#include "parser/commands.h"

#include "game/map.h"
#include "game/rules.h"
#include "game/game.h"
#include "game/structures.h"
#include "game/flags.h"


game_t flags_handling(int argc, char ** args) {
	int c;
	
	int height = 20;
	int width = 20;
	rules_t rules = load_rules("conway_moor");
	int alloc = 0;

	map_t map = alloc_map("main", height, width);
	
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
				map = load_structure(optarg);
				alloc = 1;
				break;
			case 'r':
				free(rules);
				rules = load_rules(optarg);
				break;
			case 'h':
				height = atoi(optarg);
				printf("%d\n", height );
				break;
			case 'w':
				width = atoi(optarg);
				printf("%d\n", width );
				break;		
			case '?':
				break;
			default:
				abort();
   		}
	}
	
	if(alloc == 0)
		map = alloc_map("main", height, width);
	
	return start(rules, map);
}