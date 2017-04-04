#include "parser/cmd_proxy.h"
#include "game/game_cmds.h"

int register_all_cmds(parser_t parser) {
	register_cmd(parser, "show_rules", "Help", show_rules_c);
	register_cmd(parser, "set_rules", "Help", set_rules_c);
	register_cmd(parser, "place", "Help", place_c);
	register_cmd(parser, "set_size", "Help", set_size_c);
	register_cmd(parser, "next", "Help", next_c);
	register_cmd(parser, "n", "Alias for \"next\" command", next_c);
	register_cmd(parser, "play", "Help", play_c);
	register_cmd(parser, "random", "Help", random_c);
	register_cmd(parser, "snap", "Help", snap_c);
	register_cmd(parser, "clean", "Help", clean_c);
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
    printf("Set size to %dx%d\n", atoi(command[1]), atoi(command[2]));   
	return clean(game, atoi(command[1]), atoi(command[2]));	
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

int exit_c(char **command, game_t game) {
	exit(0);
}