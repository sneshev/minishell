/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:22:32 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:19:24 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;

	total = nmemb * size;
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

// int main()
// {
//     size_t num = 5;
//     size_t size = sizeof(int);
//     int *arr = (int *)ft_calloc(num, size);
//     if (arr == NULL)
// 	{
//         printf("Memory allocation failed\n");
//         return 1;
//     }
//     printf("Array elements after ft_calloc:\n");
//     for (size_t i = 0; i < num; i++)
//         printf("arr[%zu] = %d\n", i, arr[i]);
//     free(arr);
//     return 0;
// }