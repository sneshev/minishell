#include "../minishell.h"

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

void	error_message(char const *s, int exit_code)
{
	printf("%s\n", s);
	(void)exit_code;
	exit (exit_code);
	return ;
}
