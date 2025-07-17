#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

void	enable_signals(void);
void	disable_SIGINT(void);
void	receive_SIGINT();
void	reset_signals(void);

#endif