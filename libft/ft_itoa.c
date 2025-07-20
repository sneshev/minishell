/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:21:54 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/23 18:50:29 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*charnum(int n, int len, char *ptr, int sign)
{
	ptr += len;
	*ptr = '\0';
	ptr--;
	while ((len > 1 && sign == 1) || len > 1)
	{
		*ptr = n % 10 + '0';
		n /= 10;
		ptr--;
		len--;
	}
	if (sign == -1)
		*ptr = '-';
	else
		*ptr = n % 10 + '0';
	return (ptr);
}

int	dec(int n)
{
	if (n < 10)
		return (1);
	return (1 + dec(n / 10));
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		sign;
	char	*ptr;

	sign = 1;
	len = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		sign *= -1;
		len++;
	}
	len += dec(n);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ptr = charnum(n, len, ptr, sign);
	return (ptr);
}

// int main()
// {
// 	printf("%s", ft_itoa(-2147483648));
// }