#ifndef LIST_H
# define LIST_H

// list
t_list	*create_list(t_list *list, char **tokens, int wordc);
void	update_index(char **tokens, int *index);
char	*get_cmd(char *cmd);

// list_utils
char		**get_cmd_args(char **tokens, int index);
int			count_cmd_args(char **tokens, int index);
t_list		*new_node(char **tokens, int index);
void		add_node_back(t_list **list, t_list *current);
/* void		check_cmd_access(int fd[2], char *cmd); */


// files
t_file			*get_file_list(t_file *file, char **tokens, int index, int file_count);
char			**get_redir_files(char **tokens, int index, int file_count);
t_file			*create_file_list(t_file *file, char **files);
void			create_files(int fd[2], t_file *file);
int				handle_heredoc(t_file *file);

// files_utils
void			add_filenode_back(t_file **file, t_file *current);
t_file			*new_file_node(char *redir_type, char *filename);
int				count_redir_files(char **tokens, int index);
t_redir_type	find_redir_type(char *str);

// free
void	free_env_node(t_env **prev_env);
void	free_list_node(t_list **prev_list);
void	free_file_node(t_file **prev_file);



#endif