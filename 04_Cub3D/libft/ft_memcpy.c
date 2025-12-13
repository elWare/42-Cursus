/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:32:10 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 13:32:11 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst1;
	unsigned char	*src1;
	size_t			len;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	len = 0;
	while (len < n)
	{
		dst1[len] = src1[len];
		len++;
	}
	return (dst1);
}
/*The memcpy() function copies n bytes from memory area src to memory area dst.
    If dst and src overlap, behavior is undefined.  Applications in which dst
    and src might overlap should use memmove(3) instead.*/
