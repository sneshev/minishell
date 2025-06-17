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

void	free_node(t_list **node_ptr) // hella leaks for now.
{
	t_list	*node;

	if (!node_ptr || !*node_ptr)
		return ;
	node = *node_ptr;
	if (node->cmd.cmd)
		free(node->cmd.cmd);
	if (node->cmd.args)
		free_arr(node->cmd.args);
	// if (node->cmd.pipe)
		// free(node->cmd.pipe);
	//need to free the infiles and outfiles	
	free(node);
	node = NULL;
}

void	free_list(t_list **list)
{
	t_list	*temp;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free_node(&temp);
	}
	*list = NULL;
}
