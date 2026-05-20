/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:16:51 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/17 12:42:00 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
void	ft_print_int(int numb)
{
	char c;
	
	if (numb > 9)
	{
		ft_print_int(numb / 10);
		numb = numb % 10;
	}
	c = numb + '0';
	write(1, &c, 1);
}
int	main(int argc, char **argv)
{
	(void)argv;
	ft_print_int(argc - 1);
	write(1, "\n", 1);
	return (0);
}