#include "../minishell.h"

bool is_space(char c)
{
    if (c == 32)
        return (true);
    else
        return (false);
}

int	word_count(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
		{
			j++;
			while (s[i] != ' ' && s[i] != '\0')
				i++;
		}
	}
	return (j);
}

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

void *xmalloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("minishell: xmalloc: cannot allocate )", 2);
		ft_putnbr_fd((int)size, 2);
		ft_putstr_fd(" bytes (errno 12: Cannot allocate memory)", 2);
		exit_with_code(1);
	}
	return (ptr);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("%s\n",arr[i]);
		i++;
	}
}

void	perror_message(char *s)
{
	// printf("minishell: %s: %s", s, message);
	printf("%s: command not found", s);
	printf("\n");
}

void	write_err(char *keyword, char *message)
{
	if (keyword)
	{
		write(2, keyword, ft_strlen(keyword));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

// MUST BE NULL TERMINATED
int	count_strings(char **arr, bool count_empty)
{
	int		count;
	size_t	i;

	if (!arr)
		return (-1);
	count = 0;
	i = 0;
	while (arr[i])
	{
		if (*(arr[i]))
			count++;
		else if (count_empty)
			count++;
		i++;
	}
	return (count);
}

long	ft_atol(const char *nptr)
{
    long	sign;
    long	nbr;

    nbr = 0;
    sign = 1;
    while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
        nptr++;
    if (*nptr == '-' || *nptr == '+')
    {
        if (*nptr == '-')
            sign = -1;
        nptr++;
    }
    while (*nptr >= '0' && *nptr <= '9')
    {
        nbr = nbr * 10 + (*nptr - '0');
        nptr++;
    }
    return (nbr * sign);
}
