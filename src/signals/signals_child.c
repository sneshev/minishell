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










// void heredoc_SIGINT(int sig)
// {
//     (void)sig;
//     g_signal = 0;
//     ft_putstr_fd("\n", STDERR_FILENO);
//     rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void heredoc_signals(void)
// {
//     struct sigaction	sa;

//     ft_bzero(&sa, sizeof(sa));
//     sa.sa_handler = heredoc_SIGINT;
//     sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// }