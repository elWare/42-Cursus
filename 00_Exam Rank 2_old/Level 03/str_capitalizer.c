/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:09:06 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/27 10:15:52 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_capitalizer(char *str)
{
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
		if (*str >= 'a' && *str <= 'z')
		{	
			*str -=32;
			str++;
		} 
		else if (*str >= 'A' && *str <= 'Z')
			str++;
		while (*str && *str != ' ' && *str != '\t')
		{
			if (*str >= 'A' && *str <= 'Z')
				*str +=32;
			str++;
		}
	}
	
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

int	main(int argc, char **argv)
{
	int i = 1;
	if (argc >= 2)
	{
		while (argc > i )
		{
			ft_capitalizer(argv[i]);
			ft_putstr(argv[i]);
			i++;
			write(1, "\n", 1);
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}