/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:06:48 by sneshev           #+#    #+#             */
/*   Updated: 2025/08/11 18:54:15 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "signals.h"
#include <readline/readline.h>

/*
    Have to make CTRL-C (SIGINT) stop the running child process
    Have to make CTRL-\ (SIGQUIT) stop the running child process with core dump
    
    otherwise done :p
*/

volatile sig_atomic_t	g_signal = 0;

// Ctrl + c (only outside of process)
void	receive_sigint(int sig)
{
	(void)sig;
	g_signal = 0;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	set_exit_code(130);
}

void	redirect_sigint(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = receive_sigint;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	disable_sigint(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	disable_sigquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}

void	enable_signals(void)
{
	redirect_sigint();
	disable_sigquit();
}
