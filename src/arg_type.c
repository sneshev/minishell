#include "minishell.h"

// bool	is_command(char *str, char **envp)
// {
// 	char	*path;
// 	char	**paths;
// 	char	*full_cmd;
// 	int		i;

// 	if (str[0] == '/' || str[0] == '.')//more checks for this?
// 		return (str);
// 	i = 0;
// 	path = get_env(envp);
// 	paths = get_path(path, str);
// 	if (!paths)
// 		return (perror("malloc error message\n"), NULL);
// 	while (paths[i])
// 	{
// 		full_cmd = ft_strdup(paths[i]);
// 		if (!full_cmd)
// 			return (free_path(paths[i]), NULL);
// 		if (access(full_cmd, F_OK) == 0)
// 			return (free_path(paths, i), full_cmd);//have to double check how the i works in freeing the paths
// 		free(full_cmd);
// 		i++;
// 	}
// 	free_path(paths, i);
// 	return (NULL);
// }

bool is_redirect(char *str)
{
	if (!(*str))
		return (false);
	if (*str == '<')
	{
		str++;
		if (*str == '\0')
			return (true);
		if (*str == '<' && (*(str + 1) == '\0'))
			return (true);
	}	
	else if (*str == '>')
	{
		str++;
		if (*str == '\0')
			return (true);
		if (*str == '>' && (*(str + 1) == '\0'))
			return (true);
	}
	return (false);
}

bool	is_pipe(char *str)
{
	if (*str == '|' && *(str + 1) == '\0')
		return (true);
	return (false);
}