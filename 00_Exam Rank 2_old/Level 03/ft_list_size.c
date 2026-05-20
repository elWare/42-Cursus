/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:27:15 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/16 08:42:04 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list_size.h"
#include <unistd.h>

int	ft_list_size(t_list *begin_list)
{
	int	len;

	if (begin_list == NULL)
		return (0);
	len = 1;
	while(begin_list->next == NULL)
	{
		begin_list = begin_list->next;
		len++;
	}
	return (len);
}
