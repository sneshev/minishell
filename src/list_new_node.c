#include "minishell.h"

static t_redir_type find_redir_type(char *str)
{
	if (*str == '<')
	{
		str++;
		if (*str != '<')
			return (REDIR_IN);
		else
			return (REDIR_HEREDOC);
	}
	else
	{
		str++;
		if (*str != '>')
			return (REDIR_OUT);
		else
			return (REDIR_APPEND);
	}
}

static void	add_filenode_back(t_file **file, t_file *current)
{
	t_file	*temp;

	if (*file == NULL)
	{
		*file = current;
		return ;
	}
	temp = *file;
	while (temp->next)
		temp = temp->next;
	temp->next = current;
}

// void	handle_files(t_list **list)
// {

// }


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

// int add_redirection(char **tokens, int *index, t_list **node_ptr)
// {
// 	t_list	        *node;
//     t_file          *new_file;

//     if (!tokens[*index] || !tokens[*index][0]
//         || !tokens[*index + 1] || !tokens [*index + 1][0])
//         return (-1);

//     new_file = (t_file *)malloc(sizeof(t_file));
//     if (!new_file)
//         return (-1);
//     new_file->next = NULL;
//     new_file->type = is_redirection(tokens[*index]);
//     (*index) += 1;
//     new_file->filename = ft_strdup(tokens[*index]);
//     if (new_file->type == NONE || !(new_file->filename))
//         return (free_file_node(&new_file), -1);
//     (*index) += 1;

//     node = *node_ptr;

//     if (new_file->type == REDIR_IN || new_file->type == REDIR_HEREDOC)
//     {
//         add_filenode_back(&(node->infiles), new_file);
//     }
//     else if (new_file->type == REDIR_OUT || new_file->type == REDIR_APPEND)
//     {
//         add_filenode_back(&(node->outfiles), new_file);
//     }
//     else
//         return (free_file_node(&new_file), -1);
//     return (1);
// }

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

int		count_cmd_args(char **tokens, int index)
{
	int	count;

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

int	count_redir_files(char **tokens, int index)
{
	int	count;

	count = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
		{
			count += 2;
			index += 2;
		}
		else
			index++;
	}
	return (count);
}

char	**get_cmd_args(char **tokens, int index)
{
	int		arg_count;
	char	**args;
	int		i;

	arg_count = count_cmd_args(tokens, index);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
			index += 2;
		else
		{
			args[i] = ft_strdup(tokens[index]);
			if (!args[i])
				return (free_arr(args), NULL);
			i++;
			index++;
		}
	}
	args[i] = NULL;
	return (args);
}

char	**get_redir_files(char **tokens, int index)
{
	char	**files;
	int		i;

	files = malloc(sizeof(char *) * (count_redir_files(tokens, index) + 1));
	if (!files)
		return (NULL);
	i = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
		{
			files[i] = ft_strdup(tokens[index]);
			if (!files[i])
				return (free_arr(files), NULL);
			files[i + 1] = ft_strdup(tokens[index + 1]);
			if (!files[i + 1])
				return (free_arr(files), NULL);
			i += 2;
			index += 2;
		}
		else
			index++;
	}
	files[i] = NULL;
	return (files);
}

t_file	*new_file_node(char *redir_type, char *filename)
{
	t_file	*node;

	node = malloc(sizeof(t_file));
	if (!node)
		return (NULL);
	node->type = find_redir_type(redir_type);
	node->filename = ft_strdup(filename);
	if (!node->filename)
		return (NULL);
	node->next = NULL;
	return node;
}

t_file	*put_redir_files(t_file **file, char **files)
{
	t_file	*new;
	int		i;

	new = NULL;
	i = 0;
	while (files[i] && files[i + 1])
	{
		new = new_file_node(files[i], files[i + 1]);
		if (!new)
			return (free_file(file), NULL);
		add_filenode_back(file, new);
		i += 2;
	}
	return (*file);
}

int	handle_heredoc(t_file **file)
{
	(void)file;
	printf("heredoc\n");
	return (0);
}

t_file	*create_files(t_cmd **cmd, t_file **file)
{
	t_file	*temp;
	int		infile;
	int		outfile;

	temp = *file;
	while (temp)
	{
		if (temp->type == REDIR_IN)
			infile = open(temp->filename, O_RDONLY, 0400);
		else if (temp->type == REDIR_HEREDOC)
			handle_heredoc(&temp);
		else if (temp->type == REDIR_OUT)
			outfile = open(temp->filename, O_TRUNC | O_WRONLY | O_CREAT, 0200);
		else if (temp->type == REDIR_APPEND)
			outfile = open(temp->filename, O_WRONLY | O_CREAT, 0200);
		if (outfile == -1 || infile == -1)
			return (NULL);
		temp = temp->next;
	}
	(*cmd)->input = infile;
	(*cmd)->output = outfile;
	return (*file);
}

t_cmd	*set_cmd(t_cmd **cmd, char **tokens, int index)
{
	char	**args;
	char	**files;
	t_file	*file;

	args = get_cmd_args(tokens, index);
	if (!args)
		return (NULL);
	(*cmd)->cmd = args[0];
	(*cmd)->args = args;
	files = get_redir_files(tokens, index);
	file = NULL;
	put_redir_files(&file, files);
	if (!file)
		return (free_arr(args), NULL);
	free_arr(files);
	create_files(cmd, &file);
	return (*cmd);
}

void	initialize_cmd(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->args = NULL;
	(*cmd)->input = -1;
	(*cmd)->output = -1; 
}

int	main(void)
{
	char *s = " cmd1 arg1 arg2 > outfile1 > outfile2    < invalid arg3  >outfile3   arg4 arg5 arg6|arg7>outfile4";
	char **tokens = get_tokens(s);
	if (!tokens)
		return (0);
	t_cmd *cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	initialize_cmd(&cmd);
	set_cmd(&cmd, tokens, 0);
	print_cmd(cmd);
	return (0);
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

t_list	*new_node(char **tokens, int index)
{
	t_list	*node = NULL;

	(void)tokens;
	(void)index;
	// node = malloc(sizeof(t_list));
	// if (!node)
	// 	return (NULL);
	// fill_new_node(&node);

    // while (is_redirection(tokens[*index]) != NONE)
	// {
	// 	if (add_redirection(tokens, index, &node) == -1)
    //         return (free_node(&node), NULL);
	// }
    
    // if (add_cmd(tokens[*index], &node) == -1)
    // {
    //     return (free_node(&node), NULL);
    // }
    // (*index) += 1;
    
    // if (count_cmd_args(tokens, *index) > 0)
    // {
    //     node->cmd.args = (char **)malloc((count_cmd_args(tokens, *index) + 1) * sizeof(char *));
	//     if (!node->cmd.args)
    //         return (free_node(&node), NULL);
    //     node->cmd.args = NULL;
    // }

    // while (tokens[*index] && !is_pipe(tokens[*index]))
	// {
    //     if (is_redirection(tokens[*index]) != NONE)
    //     {
    //         if (add_redirection(tokens, index, &node) == -1)
    //             return (free_node(&node), NULL);
    //     }
    //     else
    //     {
    //         if (add_arg(tokens[*index], index, &node) == -1)
    //             return (free_node(&node), NULL);
    //     }
	// }
    
    // if (tokens[*index] && is_pipe(tokens[*index]))
    // {
    //     *index += 1;
    // }
	
    return (node);
}


// WE NEED:

// 1. function that assigns the tokentype according to position
// 2. for this function we put redirection files and command arguments (including the command) in two seperate string arrays, so we need functions that calculate for how many of these (files/args) we need to malloc
// 3. we need a function that checks the infiles/creates the outfiles and then set the input and output. ofcourse if there are no invalid files. however, if this is the case, we delete the entire node (and need to make sure to not return error as this will terminate the whole process, we only need to terminate this single node and continue to after a possible pipe)