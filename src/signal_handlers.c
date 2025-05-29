#include "minishell.h"

volatile sig_atomic_t	g_signal = -1;

// void	handle_signals(int sig)
// {
// 	(void)sig;
// 	printf("\033[0;32m%d\033[0m", g_signal);
// 	if (g_signal == -1)
// 	{
// 		write(1, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		return ;
// 	}
// 	else
// 	{
// 		g_signal = sig;
// 		write(1, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		// rl_redisplay();
// 	}
// }

void printsig()
{
	if (g_signal == -1)
		printf("\033[0;32m%d ()\033[0m", g_signal);
	if (g_signal == 0)
		printf("\033[0;32m%d (line read)\033[0m", g_signal);
	if (g_signal == 2)
		printf("\033[0;32m%d (ctrl + c'ed)\033[0m", g_signal);
	fflush(NULL);
}

void	handle_signals(int sig)
{
	printsig();
	if (g_signal == 0)
	{
		g_signal = sig;
		write(1, "\n", 1);
	}
	else
	{
		write(1, "^C\nminishell$ ", 15);
	}
}

void reset_signal(char *line)
{
	printf("	\033[0;31mresetting signal%d -> ", g_signal);
	g_signal = -1;
	printf("%d \033[0m	", g_signal);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free(line);
}