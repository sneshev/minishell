#include "minishell.h"

// Ctrl + c (only outside of process)
void receive_SIGINT()
{
    g_signal = 0;
    ft_putstr_fd("\n", STDERR_FILENO);
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}