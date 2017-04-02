#include <stdio.h>
#include <string.h>

#include "parser/cmd.h"
#include "parser/help.h"
#include "game/game_cmds.h"

int wait_cmd(game_t game) {
	char cmd[MAX_NAME_LENGTH];
	printf("Game of Life> ");
	scanf("%s", cmd);
	
	int tmp;
	int tmp2;
	char stmp[MAX_NAME_LENGTH];
	
	
	if(strcmp(cmd, "help") == 0)
		show_gol_help();
	else if(strcmp(cmd, "n") == 0)
		move(game, 1, 0, NULL);
	else if(strcmp(cmd, "play") == 0) {
		scanf("%d", &tmp);
		scanf("%d", &tmp2);
		scanf("%s", stmp);
		move(game, tmp, tmp2, stmp);
	}
	else if(strcmp(cmd, "place") == 0) {
		scanf("%d", &tmp);
		scanf("%d", &tmp2);
		int actives[] = {(tmp * game->map->width) + tmp2};
		place(game, (int*)actives, 1);
		printf("Placed cell in %d %d\n", tmp, tmp2);
	}
	else if(strcmp(cmd, "random") == 0) {
		scanf("%d", &tmp);
		random_map(game, tmp);
		move(game, 1, 0, NULL);
	}
	else if(strcmp(cmd, "clean") == 0) {
		clean(game, game->map->height, game->map->width);
		move(game, 1, 0, NULL);
	}
	else if(strcmp(cmd, "set_size") == 0) {
		scanf("%d", &tmp);
		scanf("%d", &tmp2);
		clean(game, tmp, tmp2);
		printf("Set size to %dx%d\n", tmp, tmp2);
	}
	else if(strcmp(cmd, "exit") == 0)
		return 0;
		
	return 1;
}