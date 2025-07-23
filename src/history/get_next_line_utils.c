/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:12:57 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/21 18:08:37 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		ptr[i] = *s2;
		i++;
		s2++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*ptr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = 1;
	while (s[len - 1])
		len++;
	ptr = malloc(len);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	find_nl(const char *s)
{
	int	i;

	i = 1;
	if (s == NULL)
		return (-1);
	while (*s)
	{
		if (*s == '\n')
			return (i);
		s++;
		i++;
	}
	return (-1);
}
