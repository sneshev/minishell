/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:41:11 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:14:39 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
// void to_upper(unsigned int index, char *ch)
// {
//     if (*ch >= 'a' && *ch <= 'z' && index != 1337)
//         *ch -= 32;
// }

// int main()
// {
//     char str[] = "hello world!";
//     ft_striteri(str, to_upper);
//     printf("%s\n", str);
//     return 0;
// }