/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:01:50 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/25 22:05:54 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

void	enable_signals(void);
void	disable_sigint(void);
void	receive_sigint(int sig);
void	reset_sigint(void);
void	reset_signals(void);

#endif