#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
	arr = NULL;
}


bool is_quote(char c)
{
    if (c == '\'')
        return (true);
    else if (c == '\"')
        return (true);
    else
        return (false);
}

bool is_space(char c)
{
    if (c == 32)
        return (true);
    else
        return (false);
}

// return (-2); for unclosed brackets
int count_args(char *str)
{
    int count;
    int quote_type;

    if (!str)
        return (-1);
    count = 0;
    while (*str)
    {
        quote_type = 0;
        while (is_space(*str))
            str++;
        if (*str)
        {
            count++;
            while(*str && !is_space(*str)) 
            {
                if (is_quote(*str))
                {
                    quote_type = *str;
                    str++;
                    while (*str && *str != quote_type)
                        str++;
                    if (*str == '\0')
                        return (-2);
                }    
                str++;
            }
        }
    }
    return (count);
}

// return (-2); for unclosed brackets
int find_arg_len(char *str)
{
    int count;
    int quote_type;

    count = 0;
    while (is_space(*str))
        str++;

    if (*str)
    {
        while(*str && !is_space(*str))
        {
            count++;
            if (is_quote(*str))
            {
                quote_type = *str;
                while (*(++str))
                {
                    count++;
                    if (*str == quote_type)
                        break ;
                    if (*(str + 1) == '\0')
                        return (-2);
                }
            }
            str++;
        }
    }
    return (count);
}

void add_arg(char **arr, int index,char *str, int arg_len)
{
    int j;

    arg_len = find_arg_len(str);
    arr[index] = (char *)malloc((arg_len + 1) * sizeof(char));
    if (!arr[index])
        return ;
    
    j = 0;
    while(j < arg_len)
    {
        arr[index][j] = str[j];
        j++;
    }
    arr[index][j] = '\0';
}

char **get_args(char *str)
{
    char **arr = NULL;
    int total_args;
    int arg_len;
    int index;
    int j;

    total_args = count_args(str);
    arr = (char **)malloc((total_args + 1) * sizeof(char *));
    if (!arr)
        return (NULL);
    index = 0;
    while (index < total_args)
    {
        while (is_space(*str))
            str++;
        add_arg(arr, index, str, arg_len);
        str += find_arg_len(str);
        if (!arr[index])
        {
            free_arr(arr);
            return (NULL);

        }
        index++;
    }
    arr[index] = NULL;
    return (arr);
}


int main()
{
    char *str = "cat README.tx | grep \"Hello World!\"";
    char **args = get_args(str);
    int i = 0;
    while (args[i])
    {
        printf("args[%d]: %s\n", i, args[i]);
        free(args[i]);
        i++;
    }
    free(args);
}







// bool	is_valid_input(char *line, char **envp)
// {
// 	t_node	*list;
// 	char	**args;
// 	int		wordc;

// 	args = get_args(line);
// 	if (!args)
// 		return (false);//should we specify its a malloc error?
// 	wordc = word_count(line);
// 	list = NULL;
// 	create_list(&list, args, wordc, envp);
// 	free_arr(args);
// 	if (!list)
// 		return (false);
// 	print_list(list);
// 	free_list(&list);
// 	return (true);
// }

void	handle_invalid_input(void)
{

}