/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:32:30 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 13:32:32 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*let;

	let = (unsigned char *)dest;
	while (len > 0)
	{
		*let++ = (unsigned char)c;
		len--;
	}
	return (dest);
}
/*The memset() function writes len bytes of value c (converted to an unsigned
	char) to the string b. The memset() function returns its first argument*/