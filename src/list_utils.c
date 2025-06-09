#include "minishell.h"

void	free_node(t_list **node_ptr)
{
	t_list	*node;

	if (!node_ptr)
		return ;
	node = *node_ptr;
	if (node)
	{
		if (node->arg)
			free(node->arg);
		free(node);
		node = NULL;
	}
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
