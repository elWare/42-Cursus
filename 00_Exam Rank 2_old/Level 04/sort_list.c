/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:31:54 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/25 11:32:30 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
    int tmp;                                  // to store the data of the nodes
    t_list *begin = lst;                  // to store the beginning of the list

    while (lst && lst->next)                // while there are nodes to compare
    {
        if ((*cmp)(lst->data, lst->next->data) == 0) 
                                                 // if the data is not in order
        {
            tmp = lst->data;                // store the data of the first node
            lst->data = lst->next->data;   // store the data of the second node
            lst->next->data = tmp;          // store the data of the first node
            lst = begin;                      // start again from the beginning
        }
        else
            lst = lst->next;  // if the data is in order, move to the next node
    }
    return (begin);                         // return the beginning of the list
}
