#include "minishell.h"

void	print_list(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d	list->line: %s\n", i, list->arg);
		printf("%d	list->arg_type: %d\n", i, list->arg_type);
		printf("-----------------------\n");
		list = list->next;
		i++;
	}
}

void	free_node(t_node **node_ptr)
{
	t_node	*node;

	if (!node_ptr)
		return ;
	node = *node_ptr;
	if (node)
	{
		if (node->arg)
			free(node->arg);
		// if (node->next)
			// free(node->next);
		free(node);
		node = NULL;
	}
}

void	free_list(t_node **list)
{
	t_node	*temp;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free_node(&temp);
	}
	*list = NULL;
}
