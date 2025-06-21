#include "minishell.h"

char **ft_realloc(char **old, size_t new_size)
{
    char **new;
    size_t j = 0;


	new = malloc(sizeof(char *) * (new_size + 1));
    if (!new)
        return NULL;

    while (old && old[j] && j < new_size)
    {
        new[j] = old[j];
        j++;
    }

    while (j < new_size)
    {
        new[j] = NULL;
        j++;
    }

    new[new_size] = NULL; 
    free(old);
    return new;
}

void	free_file_node(t_file **node_ptr)
{
	t_file	*node;

	if (!node_ptr || !*node_ptr)
		return ;
	node = *node_ptr;
	if (node->filename)
		free(node->filename);
	free(node);
}

void	free_file(t_file **file)
{
	t_file	*temp;

	while (*file)
	{
		temp = *file;
		*file = (*file)->next;
		free_file_node(&temp);
	}
	*file = NULL;
}

void	free_cmd_node(t_cmd **cmd_ptr)
{
	t_cmd	*node;

	if (!cmd_ptr || !*cmd_ptr)
		return ;
	node = *cmd_ptr;
	if (node->cmd)
		free(node->cmd);
	if (node->args)
		free_arr(node->args);
	node = NULL;
}

void	free_list_node(t_list **list_ptr)
{
	(void)list_ptr;
	// t_list	*node;

	// if (!list_ptr || !*list_ptr)
	// 	return ;
	// node = *list_ptr;
	// if (&node->cmd)
	// 	free_cmd_node(&node->cmd);
	// node = NULL;
}

void	free_list(t_list **list)
{
	t_list	*temp;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free_list_node(&temp);
	}
	*list = NULL;
}


void	free_env_node(t_env **env_ptr)
{
	t_env	*node;


	if (!env_ptr || !*env_ptr)
		return ;
	node = *env_ptr;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	node = NULL;
}

void	free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free_env_node(&temp);
	}
	*env = NULL;
}
