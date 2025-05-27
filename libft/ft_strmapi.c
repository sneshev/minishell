/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 21:01:42 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 16:37:14 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	if (!s || !f)
		return (NULL);
	while (s[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// static char	to_upp(unsigned int index, char ch)
// {
// 	if (ch >= 'a' && ch <= 'z' && index != 1337)
// 	{
// 		ch -= 32;
// 	}
// 	return (ch);
// }

// int main()
// {
//     char str[] = "hello world!";
// 	char *result = ft_strmapi(str, to_upper);
//     if (result)
// 	{
// 		printf("new string: %s\n", result);
// 		free(result);
// 	}
// 	else 
// 		printf("Oopsie");
// 	return 0;
// }