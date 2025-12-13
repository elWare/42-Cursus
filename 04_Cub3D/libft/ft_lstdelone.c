/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:30:46 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 13:30:48 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst -> content);
	free(lst);
}
/*Takes an 'lst' node as a parameter and releases the memory of the content 
	using the 'del' function given as a parameter, in addition to releasing 
	the node. The 'next' memory should not be freed. Parameters lst: the 
	node to release. del: a pointer to the function used to release the 
	content of the node.*/