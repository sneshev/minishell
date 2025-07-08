#ifndef TOKENS_H
# define TOKENS_H



// utils
int		redir(char *str);
bool	is_space(char c);
bool	is_quote(char c);

// env variables
int     add_env_variable(char *dest, char *src, int *j, t_env *env);
int		find_varname_len(char *str);
int		find_envvar_len(char *str, t_env *env);
char	*find_envvar(char *str, t_env *env);


// quotes
int		find_quote_len(char *str, t_env *env, bool count_quote, bool expand_envvar);		// doesnt do env vars yet
void	add_quoted_sequence(char *dest, char *src, int *j, t_env *env);	// doesnt do env vars yet


#endif