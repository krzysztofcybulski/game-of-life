#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "utils/colors.h"

#include "game/game.h"
#include "game/rules.h"
#include "game/map.h"
#include "game/golsh.h"

void print_map(game_t game) {
	int i, j;
	map_t map = game->map;
	
	printf("\n%d\n", game->age);
	
	for(i = 0; i < map->height; i++) {
		for(j = 0; j < map->width; j++)
			printf("%d", get(map, j, i) > 0 ? get(map, j, i) : 0);
		printf("\n");
	}
}
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
	
	flags_handling(argc, argv);
	//TEST RULES
	rules_t r = (rules_t) malloc(sizeof(rules_t));
	r->name = "test";
	int live[2] = {4, 5};
	r->live = (int*)live;
	int born[1] = {-4};
	r->born = (int*)born;
	int neighbors[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	int (*ne)[2] = neighbors;
	r->neighbors_amount = 8;
	r->neighbors = malloc(sizeof(ne));
	r->neighbors = ne;
	
	map_t map = alloc_map(5, 5);
	
	game_t game = start(r, map);
	game->map->cells[12] = 1;
	game->active = malloc(sizeof(int));
	game->active[0] = 12;
	game->active_amount = 1;
	
	print_map(game);
	step(game);
	print_map(game);
	
	golsh_loop();
	
	return EXIT_SUCCESS;
}
