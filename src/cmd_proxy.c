#include "parser/cmd_proxy.h"

#include "game/rules.h"
#include "game/map.h"
#include "game/game_cmds.h"
#include "game/structures.h"
#include "parser/parser.h"

int register_all_cmds(parser_t parser) {
	register_cmd(parser, "show_rules", 		"Shows all available rules to choose from", show_rules_c);
	register_cmd(parser, "show_maps", 		"Shows all available maps to choose from", show_maps_c);
	register_cmd(parser, "set_rules",		"Sets <name> rules (see available by entering \"show_rules\")", set_rules_c);
	register_cmd(parser, "place", 			"Changes cell state", place_c);
	register_cmd(parser, "set_size", 		"Set map <height> and <width>", set_size_c);
	register_cmd(parser, "next", 			"Goes to next generation", next_c);
	register_cmd(parser, "n", 				"Alias for \"next\" command", next_c);
	register_cmd(parser, "play", 			"Shows <n> generations every <delay> milisecons and snaps them to <filename>", play_c);
	register_cmd(parser, "random", 			"Creates random map with <density> density", random_c);
	register_cmd(parser, "snap", 			"Snaps current genration to <filename>", snap_c);
	register_cmd(parser, "clean", 			"Cleans map", clean_c);
	register_cmd(parser, "save", 			"Saves map to <filename>", save_c);
	register_cmd(parser, "load", 			"Loads <filename> map", load_c);
	register_cmd(parser, "exit", 			"Exits program", exit_c);
	return 1;
}

int show_rules_c(char **command, game_t game) {
	return print_dir("resources/rules/");
}

int show_maps_c(char **command, game_t game) {
	return print_dir("resources/structures/");
}

int set_rules_c(char **command, game_t game) {
	rules_t rules = load_rules(command[1]);
	free(game->rules);
	game->rules = rules;
	printf("Rules set to %s!\n", command[1]);
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
	printf("Load map %s!\n", command[1]);

	recalculate(game);

	return 1;
}

int exit_c(char **command, game_t game) {
	printf("Goodbye!\n");
	exit(0);
}