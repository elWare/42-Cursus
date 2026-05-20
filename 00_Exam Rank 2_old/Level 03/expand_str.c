/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:52:23 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/27 09:37:20 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
	int i = 0;
	
	if (argc == 2)
	{
		while (argv[1][i] == ' ' || argv[1][i] == 9)
			i++;
		while (argv[1][i])
		{
			if (argv[1][i] == ' ' || argv[1][i] == 9)
			{
				i++;
				if (argv[1][i] != ' ' && argv[1][i] != 32 && argv[1][i])
					write(1, "   ", 3);
			}
			else
			{
				write(1, &argv[1][i], 1);
				i++;
			}
		}
	}
	write(1, "\n", 1);
	
}
