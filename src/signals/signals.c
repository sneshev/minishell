// #include "../minishell.h"
// #include <readline/readline.h>
// #include "signals.h"

// /*
//     Have to make CTRL-C (SIGINT) stop the running child process
//     Have to make CTRL-\ (SIGQUIT) stop the running child process with core dump
    
//     otherwise done :p
// */

// volatile sig_atomic_t	g_signal = 0;


// // Ctrl + c (only outside of process)
// void receive_SIGINT()
// {
//     g_signal = 0;
//     ft_putstr_fd("\n", STDERR_FILENO);
//     rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }


// void enable_SIGINT()
// {
//     struct sigaction	sa;

//     ft_bzero(&sa, sizeof(sa));
//     sa.sa_handler = receive_SIGINT;
//     sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// }


// void enable_signals(void)
// {
//     enable_SIGINT();
// }
