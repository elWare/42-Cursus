/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:31:24 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 13:31:25 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		nbr;

	nbr = 0;
	while (lst != (void *)0)
	{
		lst = lst->next;
		nbr++;
	}
	return (nbr);
}
/*Counts the number of nodes in a list. 
	lst parameters: the beginning of the list. 
	Return value: The length of the list.*/