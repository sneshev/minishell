#include "minishell.h"

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

int arg_len(char *str)
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
                quote_type = is_quote(*str);
                while (++(*str))
                {
                    count++;
                    if (*str == quote_type)
                        break ;
                }
            }
            str++;
        }
    }
    return (count);
}

char **get_args(char *str)
{
    char **args = NULL;
    int arg_amount;
    int index;

    arg_amount = count_args(str);
    args = (char **)malloc((arg_amount + 1) * sizeof(char *));
    if (!args)
        return (NULL);
    index = 0;
    while (index < arg_amount)
    {
        
    }    

    return (args);
}


int main()
{
    char *str = "\' hey\'  \"iamstepcjho i am\'  \' a god\"   \'";
    arg_len(str);

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