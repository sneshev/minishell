#ifndef LIST_H
# define LIST_H

// list
t_list	*create_list(t_list *list, char **tokens, int wordc, char **envp);
t_list	*new_node(int fd[2], char **tokens, int index);
void	add_node_back(t_list **list, t_list *current);
void	update_index(char **tokens, int *index);



// list_utils
void		create_files(int fd[2], t_file *file);
int			handle_heredoc(t_file **file);
t_file		*create_file_list(t_file *file, char **files);
t_file		*get_file_list(t_file *file, char **tokens, int index, int file_count);
t_file		*new_file_node(char *redir_type, char *filename);
char		**get_cmd_args(char **tokens, int index);
char		**get_redir_files(char **tokens, int index, int file_count);
int			count_redir_files(char **tokens, int index);
int			count_cmd_args(char **tokens, int index);
void		add_filenode_back(t_file **file, t_file *current);
void		check_cmd_access(int fd[2], char *cmd);

// free
void	free_env_node(t_env **prev_env);
void	free_list_node(t_list **prev_list);
void	free_file_node(t_file **prev_file);



#endif