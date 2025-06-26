#include "minishell.h"

void	free_file_node(t_file **prev_file)
{
	if (!prev_file || !*prev_file)
		return ;
	if ((*prev_file)->filename)
		free((*prev_file)->filename);
	free(*prev_file);
	*prev_file = NULL;
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

void	free_list_node(t_list **prev_list)
{
	if (!prev_list || !*prev_list)
		return ;
	if ((*prev_list)->cmd)
		free((*prev_list)->cmd);
	if ((*prev_list)->args)
		free_arr((*prev_list)->args);
	free(*prev_list);
	*prev_list = NULL;
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

void	free_env_node(t_env **prev_env)
{
	if (!prev_env || !*prev_env)
		return ;
	if ((*prev_env)->name)
		free((*prev_env)->name);
	if ((*prev_env)->value)
		free((*prev_env)->value);
	free(*prev_env);
	*prev_env = NULL;
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

// char **ft_realloc(char **old, size_t new_size)
// {
//     char **new;
//     size_t j = 0;


// 	new = malloc(sizeof(char *) * (new_size + 1));
//     if (!new)
//         return NULL;

//     while (old && old[j] && j < new_size)
//     {
//         new[j] = old[j];
//         j++;
//     }

//     while (j < new_size)
//     {
//         new[j] = NULL;
//         j++;
//     }

//     new[new_size] = NULL; 
//     free(old);
//     return new;
// }
