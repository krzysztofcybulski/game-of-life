#include "parser/cmd_proxy.h"
#include "game/game_cmds.h"
#include "game/structures.h"

#define MIN_WIDTH 2
#define MAX_WIDTH 999

int register_all_cmds(parser_t parser) {
	register_cmd(parser, "show_rules", 		"Help", show_rules_c);
	register_cmd(parser, "set_rules",		"Help", set_rules_c);
	register_cmd(parser, "place", 			"Help", place_c);
	register_cmd(parser, "set_size", 		"Help", set_size_c);
	register_cmd(parser, "next", 			"Help", next_c);
	register_cmd(parser, "n", 				"Alias for \"next\" command", next_c);
	register_cmd(parser, "play", 			"Help", play_c);
	register_cmd(parser, "random", 			"Help", random_c);
	register_cmd(parser, "snap", 			"Help", snap_c);
	register_cmd(parser, "clean", 			"Help", clean_c);
	register_cmd(parser, "save", 			"Help", save_c);
	register_cmd(parser, "load", 			"Help", load_c);
	register_cmd(parser, "exit", "Help", exit_c);
	return 1;
}

int show_rules_c(char **command, game_t game) {
	return 1;
}

int set_rules_c(char **command, game_t game) {
	return 1;
}

int place_c(char **command, game_t game) {
    int actives[] = {(atoi(command[1]) * game->map->width) + atoi(command[2])};
    printf("Placed cell in %d %d\n", atoi(command[1]), atoi(command[2]));
    return place(game, (int*)actives, 1);
}

int set_size_c(char **command, game_t game) {
	
	int width = atoi(command[2]);
	int height = atoi(command[1]);
	
	if(width < MIN_WIDTH || height < MIN_WIDTH || width > MAX_WIDTH || height > MAX_WIDTH) {
		printf("Can't create map with such size.\n");
		return 1;
	}
	else {
		printf("Set size to %dx%d\n", height, width);   
		return clean(game, height, width);	
	}    
}

int next_c(char **command, game_t game) {
	return move(game, 1, 0, NULL);		
}

int play_c(char **command, game_t game) {
    return move(game, atoi(command[1]),  atoi(command[2]), command[3]);
}

int random_c(char **command, game_t game) {
    random_map(game, atoi(command[1]));
    return move(game, 1, 0, NULL);
}

int snap_c(char **command, game_t game) {
    return snap(game, command[1]);

}
	
int clean_c(char **command, game_t game) {
    clean(game, game->map->height, game->map->width);
    return move(game, 1, 0, NULL);  
}

int save_c(char **command, game_t game) {
	printf("Saved current map to resources/structures/%s\n", command[1]);
	return save_structure(command[1], game->map);
}

int load_c(char **command, game_t game) {
	free(game->map);
	game->map = load_structure(command[1]);
	recalculate(game);
	return 1;
}

int exit_c(char **command, game_t game) {
	exit(0);
}