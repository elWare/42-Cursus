/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:20:22 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 13:20:23 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			cont;

	str = (unsigned char *)s;
	cont = 0;
	if (n == 0)
		return ;
	while (n > cont)
	{
		str[cont] = '\0';
		cont++;
	}
	return ;
}
/*The bzero() function writes n zeroed bytes to the string s.  If n is
     zero, bzero() does nothing.*/