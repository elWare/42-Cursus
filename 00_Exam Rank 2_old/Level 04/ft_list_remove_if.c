/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 08:40:58 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/25 12:27:38 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_list.c"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*ptr_nodo, *ptr_ant;
	
	if (begin_list == NULL || *begin_list == NULL)
		return ;
	ptr_nodo = *begin_list;
	ptr_ant = NULL;
	while (ptr_nodo)
	{
		if (!cmp(ptr_nodo->data, data_ref))
		{
			if (ptr_nodo == *begin_list)
			{
				*begin_list = ptr_nodo->next;				
				free (ptr_nodo);
				ptr_nodo = *begin_list;
			}
			else
			{
				ptr_ant->next = ptr_nodo->next;
				free(ptr_nodo);
				ptr_nodo = ptr_ant->next;
			}
		}
		else
		{
			ptr_ant = ptr_nodo;
			ptr_nodo = ptr_nodo->next;
		}
	}
}