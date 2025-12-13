/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:31:39 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 13:31:50 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	char	let;
	size_t	num;

	str = (char *)s;
	let = (char)c;
	num = 0;
	while (num < n)
	{
		if (str[num] == let)
			return ((void *)(str + num));
		num++;
	}
	return (0);
}
/*The memchr() function returns a pointer to the byte located, 
	or NULL if no such byte exists within n bytes.*/