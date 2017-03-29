#ifndef GOL_C_GOLSH_H
#define GOL_C_GOLSH_H

#define BUFFSIZE 1024
#define DELIM " \t\n\r\a"

void golsh_loop();
char *golsh_read_line();
char **golsh_split_line(char *);
int run(char **);
void help();



#endif
