#ifndef GOL_C_COMMAND_H
#define GOL_C_COMMAND_H

typedef struct Command {
	char *name;
	void *description;
	char *args;
	int args_n;
	int (*cmd)();
} *cmd_t;

cmd_t create_cmd(char *name, char *args, int args_n, int (*cmd)());
void *load_args(cmd_t);
int run(cmd_t cmd, ...);

#endif