#include "minishell.h"

/*
    Have to make CTRL-C (SIGINT) stop the running child process
    Have to make CTRL-\ (SIGQUIT) stop the running child process with core dump
    
    otherwise done :p
*/

volatile sig_atomic_t	g_signal = 0;

void redirect_SIGINT()
{
    struct sigaction	sa;

    ft_bzero(&sa, sizeof(sa));
    sa.sa_handler = receive_SIGINT;
    sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void disable_SIGQUIT()
{
    struct sigaction	sa;

    ft_bzero(&sa, sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}


void enable_signals(void)
{
    redirect_SIGINT();
    disable_SIGQUIT();
}
