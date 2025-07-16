#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

// child
void	reset_signals(void);
void	heredoc_signals(void);

// parent
void	enable_signals(void);
void	disable_SIGINT(void);
void	receive_SIGINT(void);


#endif