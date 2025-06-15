#include "minishell.h"

void	free_node(t_list **node_ptr)
{
	t_list	*node;

	if (!node_ptr || !*node_ptr)
		return ;
	node = *node_ptr;
	if (node->arg)
		free(node->arg);
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

void	free_env_list(t_env **env)
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
