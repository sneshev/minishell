#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_list
{
	char			*cmd;
	char			**args;
	int				input;
	int				output;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef enum e_redir_type {
	REDIR_IN,        // <
	REDIR_HEREDOC,   // <<
	REDIR_OUT,       // >
	REDIR_APPEND     // >>
}			t_redir_type;

typedef struct s_file
{
	t_redir_type	type;
	char			*filename;
	struct s_file	*next;
}	t_file;

#endif