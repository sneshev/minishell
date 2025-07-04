#include "../minishell.h"
#include "signals.h"

void reset_SIGINT()
{
    struct sigaction	sa;

    ft_bzero(&sa, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}
void reset_SIGQUIT()
{
    struct sigaction	sa;

    ft_bzero(&sa, sizeof(sa));
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}


void reset_signals(void)
{
    reset_SIGINT();
    reset_SIGQUIT();
}