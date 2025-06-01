#include "minishell.h"


#define BUILTIN 1
#define COMMAND 2
#define REDIRECTION 3
#define PIPE 4
#define STRING 5
#define SQUOTE 6
#define DQUOTE 7
#define FLAG 8


void print_type(int type)
{
	if (type == BUILTIN)
		printf("(builtin)");
	if (type == COMMAND)
		printf("(command)");
	if (type == REDIRECTION)
		printf("(redirection)");
	if (type == PIPE)
		printf("(pipe)");
	if (type == STRING)
		printf("(string)");
	if (type == SQUOTE)
		printf("(single quotes)");
	if (type == DQUOTE)
		printf("(double quotes)");
	if (type == FLAG)
		printf("(flag)");
	printf("\n");
}

void	print_list(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d	list->line: %s\n", i, list->arg);
		printf("%d	list->arg_type: %d ", i, list->arg_type);
		print_type(list->arg_type);
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
