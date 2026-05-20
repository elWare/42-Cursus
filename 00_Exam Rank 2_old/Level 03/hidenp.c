/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:40:28 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/27 10:00:49 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i,j;
	
	if (argc == 3)
	{
		i = 0;
		j = 0;
		while (argv[1][i] && argv[2][j])
		{
			if (argv[1][i] != argv[2][j])
				j++;
			else
			{
				i++;
				j++;
			}
		}
		if (!argv[1][i])
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
	write(1, "\n",1);
	return (0);
}