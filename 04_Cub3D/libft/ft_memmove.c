/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:32:19 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 13:32:20 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move_backward(char *dst, const char *src, size_t num)
{
	while (num > 0)
	{
		dst[num - 1] = src[num - 1];
		num--;
	}
}

static void	move_forward(char *dst, const char *src, size_t num)
{
	while (num > 0)
	{
		*dst = *src;
		dst++;
		src++;
		num--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst1;
	const char	*src1;
	size_t		num;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst1 = (char *)dst;
	src1 = (const char *)src;
	num = len;
	if (src1 < dst1)
		move_backward(dst1, src1, num);
	else
		move_forward(dst1, src1, num);
	return (dst);
}

/*The memmove() function copies len bytes from string src to string dst.  
    The two strings may overlap; the copy is always done in a non-destructive
    manner. The memmove() function returns the original value of dst.*/