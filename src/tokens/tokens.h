/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:10:08 by sneshev           #+#    #+#             */
/*   Updated: 2025/08/09 13:49:58 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

// add_tokens
void	add_token(char **arr, int index, char *str, t_env *env);
int		add_heredoc_tokens(char *arr[], int *index, char **str);

// utils
bool	is_heredoc(char *str);
int		redir_or_pipe(char *str);
bool	is_space(char c);
bool	is_quote(char c);

// env_variables
int		add_env_variable(char *dest, char *src, int *j, t_env *env);
int		find_varname_len(char *str);
int		find_envvar_len(char *str, t_env *env);
char	*find_envvar(char *str, t_env *env);

// quotes
int		find_quote_len(char *str, t_env *env,
			bool count_quote, bool expand_envvar);
void	add_quoted_sequence(char *dest, char *src, int *j, t_env *env);

#endif