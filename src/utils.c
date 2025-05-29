#include "minishell.h"

void free_arr(char **arr, int args)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (i < args)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}