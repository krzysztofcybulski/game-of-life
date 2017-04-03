#ifndef GOL_C_GOLSH_H
#define GOL_C_GOLSH_H

#define BUFFSIZE 1024
#define DELIM " \t\n\r\a"

void golsh_loop(game_t game);
char **golsh_split_line(char *);
int ruun(char **command, game_t game);
void help_c(char **command, game_t game);

void show_rules_c(char **command, game_t game);
void set_rules_c(char **command, game_t game);
void place_c(char **command, game_t game);
void set_size_c(char **command, game_t game);
void next_c(char **command, game_t game);
void play_c(char **command, game_t game);
void random_c(char **command, game_t game);
void snap_c(char **command, game_t game);	
void clean_c(char **command, game_t game);

#endif
