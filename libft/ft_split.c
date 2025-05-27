/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:06:29 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/24 13:24:33 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	error(char **arr, int index)
{
	int	k;

	k = 0;
	while (k < index)
	{
		free(arr[k]);
		k++;
	}
	free(arr);
}

static char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static int	wrt_out(char **arr, const char *s, char c, int index)
{
	int	word_len;
	int	j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	word_len = j;
	arr[index] = (char *)malloc((word_len + 1) * sizeof(char));
	if (!arr[index])
		return (0);
	ft_strncpy(arr[index], s, word_len);
	arr[index][word_len] = '\0';
	return (j);
}

static char	**lil_splitty(char const *s, char c, int wrdcnt, char **arr)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (s[i] && index < wrdcnt)
	{
		while (s[i] == c)
			i++;
		if (s[i])
			i += wrt_out(arr, s + i, c, index);
		if (arr[index] == NULL)
		{
			error(arr, index);
			return (NULL);
		}
		index++;
	}
	arr[index] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	int		wrdcnt;
	char	**arr;

	len = 0;
	wrdcnt = 0;
	while (s[len])
	{
		if ((len == 0 && s[len] != c) || (s[len] != c && s[len - 1] == c))
			wrdcnt++;
		len++;
	}
	arr = (char **)malloc((wrdcnt + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (lil_splitty(s, c, wrdcnt, arr));
}

// int	main()
// {
// 	char	str[] = "  I   am a genius";
// 	char	sep = ' ';
// 	char	**arr = ft_split(str, sep);
// 	for (int i = 0; arr[i] != NULL; i++)
// 	{
// 		printf("Word %d: %s\n", i + 1, arr[i]);
// 		free(arr[i]);
// 	}
// 	free(arr);
// 	return (0);
// }
