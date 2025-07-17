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
	(void)s;
	// printf("minishell: %s: ", s);
	perror("");
	// printf("\n");
}