/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:38:29 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 15:39:21 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_list
{
	char			*cmd;
	char			**args;
	int				input;
	int				output;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND
}			t_redir_type;

typedef struct s_file
{
	t_redir_type	type;
	char			*filename;
	struct s_file	*next;
}	t_file;

#endif