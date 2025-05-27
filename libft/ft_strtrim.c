/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:57:57 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 16:36:10 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*new_str(char const *s1, size_t len, size_t end)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(len - end + 1);
	if (!ptr)
		return (NULL);
	while (i < len - end)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	beg;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	beg = 0;
	end = 0;
	if (*s1 == '\0')
		return (ft_strdup(""));
	while (s1[beg] && ft_strchr(set, s1[beg]) != 0)
		beg++;
	s1 += beg;
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	while (len > end && ft_strrchr(set, s1[len - end - 1]) != 0)
		end++;
	return (new_str(s1, len, end));
}

// int main()
// {
//     char s1[] = "";
//     char set[] = "";
//     char *ptr = ft_strtrim(s1, set);
//     if (ptr)
//     {
//         printf("%s", ptr);
//         free (ptr);
//     }
//     else
//         return 0;
// }