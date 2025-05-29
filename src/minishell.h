#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>

extern volatile sig_atomic_t g_signal;


//signal handlers
void handle_signals(int sig);
void reset_signal(char *line);

//utils
void free_arr(char **arr, int args);


#endif