#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "parser/parser.h"
#include "parser/cmd_proxy.h"
#include "parser/commands.h"
#include "parser/flags.h"

#include "game/map.h"
#include "game/rules.h"
#include "game/game.h"
#include "game/structures.h"

game_t flags_handling(int argc, char ** args) {
	int height 	= DEFAULT_HEIGHT;
	int width 	= DEFAULT_WIDTH;
	
	int c;
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
				printf("Set map: %s\n", optarg );
				break;
			case 'r':
				free(rules);
				rules = load_rules(optarg);
				printf("Set rules: %s\n", optarg );
				break;
			case 'h':
				height = atoi(optarg);
				if(height < MIN_WIDTH || height > MAX_WIDTH)
					height = DEFAULT_HEIGHT;
				printf("Set height: %d\n", height );
				break;
			case 'w':
				width = atoi(optarg);
				if(width < MIN_WIDTH || width > MAX_WIDTH)
					width = DEFAULT_HEIGHT;
				printf("Set width: %d\n", width );
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