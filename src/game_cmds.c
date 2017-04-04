#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "game/game_cmds.h"
#include "game/png_generator.h"
#include "utils/colors.h"

void print_map(map_t map) {
	int i, j;
	for(i = 0; i < map->height; i++) {
		for(j = 0; j < map->width; j++)
			if(map->cells[i * map->width + j] > SPLITTER)
				printf("%s%s%s", KCYN, "★", KNRM);
			else
				printf(" ");
		printf("\n");
	}
}

void print_actives(game_t game) {
	printf("n = %d (%d)\n", game->actives_amount, game->actives_amount * (game->rules->neighbours_amount * 2 + 1));
}

int move(game_t game, int n, int delay_time, char* filename) {
	step(game);
	system("clear");
	if(filename != NULL)
		snap(game, filename);
	
	print_actives(game);
	print_map(game->map);
	
	usleep(delay_time * 1000);
	
	if(game->actives_amount == 0)
		n = 0;
	if(n > 1)
		move(game, --n, delay_time, filename);
	return 1;
}

/* !UWAGA DZIWNE ZACHOWANIE! */
int random_map(game_t game, int density) {
	int max = game->map->width * game->map->height;
	int n = max / 100 * density;
	int i;
	int k = 0;
	srand(time(NULL));
	
	int actives[max];
	
	for(i = 0; i < max; i++)
		if(rand() % 100 < density)
			actives[k++] = i;
	
	place(game, (int*)actives, n);
	return 1;
}

int clean(game_t game, int height, int width) {
	map_t new_map = alloc_map("main", height, width);
	free(game->map);
	game->actives_amount = 0;
	game->map = new_map;
	return 1;
}

int snap(game_t game, char *name) {
	char path[128];
	snprintf(path, 128, "resources/snaps/%s-%03d.png", name, game->age);
	printf("Saving to: %s\n", path);

	process_file(game->map);
	write_png_file(path);
	return 1;
}