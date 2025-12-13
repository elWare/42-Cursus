/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:31:07 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 13:31:08 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	current = lst;
	while (current)
	{
		temp = ft_lstnew(f(current->content));
		if (!temp)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, temp);
		current = current->next;
	}
	return (new_list);
}

/*Iterates the list 'lst' and applies the function 'f' to it content of each 
    node. Create a resulting list of the correct and successive application of 
    the function 'f' over each node. The 'del' function is used to delete the 
    contents of a node, if you do lack. Parameters lst: a pointer to a node.
    f: the address of a pointer to a function used in the iteration of each 
    list element. del: a function pointer used to delete the contents of a 
    node, if necessary.*/
