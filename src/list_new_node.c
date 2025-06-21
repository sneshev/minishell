#include "minishell.h"

static t_redir_type is_redirection(char *str)
{
	if (!(*str))
		return (NONE);
	if (*str == '<')
	{
		str++;
		if (*str != '<')
			return (REDIR_IN);
		if (*str == '<')
			return (REDIR_HEREDOC);
	}
	else if (*str == '>')
	{
		str++;
		if (*str != '>')
			return (REDIR_OUT);
		if (*str == '>')
			return (REDIR_APPEND);
	}
    return (NONE);
}

static void	add_filenode_back(t_file **list, t_file *current)
{
	t_file	*temp;

	if (*list == NULL)
	{
		*list = current;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = current;
}

int		count_args(char **tokens, int index)
{
	int count;

	count = 0;
	while(tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
			index += 2;
		else
		{
			count++;
			index++;
		}
	}
	return (count);
}

int add_arg(char *arg, int *index, t_list **node_ptr)
{
    t_list  *node;
    size_t  arg_count;
    char    **args;

    node = *node_ptr;
    args = node->cmd.args;
    arg_count = 0;
    if (!(*arg))
        return (-1);
    
    if (!args || !args[0] || !args[0][0])
        arg_count = 0;
    else 
    {
        while (args[arg_count])
            arg_count++;
    }

    args = (char **)ft_realloc(node->cmd.args, arg_count + 1);
    if (!args)
        return (-1);
    args[arg_count] = ft_strdup(arg);
    if (!args[arg_count])
        return (-1);
    args[arg_count + 1] = NULL;
    node->cmd.args = args;
    *index += 1;
    return (1);
}

int add_redirection(char **tokens, int *index, t_list **node_ptr)
{
	t_list	        *node;
    t_file          *new_file;

    if (!tokens[*index] || !tokens[*index][0]
        || !tokens[*index + 1] || !tokens [*index + 1][0])
        return (-1);

    new_file = (t_file *)malloc(sizeof(t_file));
    if (!new_file)
        return (-1);
    new_file->next = NULL;
    new_file->type = is_redirection(tokens[*index]);
    (*index) += 1;
    new_file->filename = ft_strdup(tokens[*index]);
    if (new_file->type == NONE || !(new_file->filename))
        return (free_file_node(&new_file), -1);
    (*index) += 1;

    node = *node_ptr;

    if (new_file->type == REDIR_IN || new_file->type == REDIR_HEREDOC)
    {
        add_filenode_back(&(node->infiles), new_file);
    }
    else if (new_file->type == REDIR_OUT || new_file->type == REDIR_APPEND)
    {
        add_filenode_back(&(node->outfiles), new_file);
    }
    else
        return (free_file_node(&new_file), -1);
    return (1);
}

int add_cmd(char *str, t_list **node_ptr)
{
    t_list  *node;

    if (!is_command(str) && !is_builtin(str))
	{
		printf("no command found: %s\n", str);
        return (-1);
    }

    node = *node_ptr;
    node->cmd.cmd = ft_strdup(str);
    if (!node->cmd.cmd)
        return (-1);
    return (1);
}

void fill_new_node(t_list **node_ptr)
{
    t_list *node;

    node = *node_ptr;
    node->cmd.cmd = NULL;
    node->cmd.args = NULL;
    node->cmd.input = -1;
    node->cmd.output = -1;
}


// t_list	*new_node(char **tokens, int *index)
// {
// 	t_list	*node;

// 	node = malloc(sizeof(t_list));
// 	if (!node)
// 		return (NULL);
// 	fill_new_node(&node);

//     while (is_redirection(tokens[*index]) != NONE)
// 	{
// 		if (add_redirection(tokens, index, &node) == -1)
//             return (free_node(&node), NULL);
// 	}
    
//     if (add_cmd(tokens[*index], &node) == -1)
//     {
//         return (free_node(&node), NULL);
//     }
//     (*index) += 1;
    
//     if (count_args(tokens, *index) > 0)
//     {
//         node->cmd.args = (char **)malloc((count_args(tokens, *index) + 1) * sizeof(char *));
// 	    if (!node->cmd.args)
//             return (free_node(&node), NULL);
//         node->cmd.args = NULL;
//     }

//     while (tokens[*index] && !is_pipe(tokens[*index]))
// 	{
//         if (is_redirection(tokens[*index]) != NONE)
//         {
//             if (add_redirection(tokens, index, &node) == -1)
//                 return (free_node(&node), NULL);
//         }
//         else
//         {
//             if (add_arg(tokens[*index], index, &node) == -1)
//                 return (free_node(&node), NULL);
//         }
// 	}
    
//     if (tokens[*index] && is_pipe(tokens[*index]))
//     {
//         *index += 1;
//     }
	
//     return (node);
// }


// WE NEED:

// 1. function that assigns the tokentype according to position
// 2. for this function we put redirection files and command arguments (including the command) in two seperate string arrays, so we need functions that calculate for how many of these (files/args) we need to malloc
// 3. we need a function that checks the infiles/creates the outfiles and then set the input and output. ofcourse if there are no invalid files. however, if this is the case, we delete the entire node (and need to make sure to not return error as this will terminate the whole process, we only need to terminate this single node and continue to after a possible pipe)