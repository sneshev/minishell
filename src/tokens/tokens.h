#ifndef TOKENS_H
# define TOKENS_H



// utils
int		redir(char *str);
bool	is_space(char c);
bool	is_quote(char c);

// quotes
int		find_quote_len(char *str, bool count_quote);			// doesnt do env vars yet
void	add_quoted_sequence(char *dest, char *src, int *j);	// doesnt do env vars yet
void	add_env_variable(char *dest, char *src, int *j);


#endif