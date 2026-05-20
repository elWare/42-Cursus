/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:29:34 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/25 11:32:35 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sort_int_tab(int *tab, unsigned int size)
{
    unsigned int i = 0;
    int tmp;

    while (i < (size - 1))              // to 5 3 1 4 2 => size = 5
    {                       
        if (tab[i] > tab[i + 1])
        {
            tmp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = tmp;
            i = 0;                      // start again from the beginning
        }
        else
            i++;
    }
}

