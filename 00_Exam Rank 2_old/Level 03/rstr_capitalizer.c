/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rstr_capitalizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:22:57 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/17 18:05:19 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_rstrcap(char *str)
{
	while(*str)
	{
		if(*str >= 'A' && *str <= 'Z')
			*str += 32;
		if((*str >= 'a' && *str <='z') &&\
			 (*(str+1) == ' ' || !*(str+1) || (*(str+1)>=9 && *(str+1)<=13)))
		{
			*str -= 32;
		}
		write(1, str, 1);
		str++;
	}
}

int	main(int argc, char **argv)
{
	int	i = 0;
	
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			ft_rstrcap(argv[i]);
			write(1, "\n", 1);
			i++;
		}
	}
	else
		write(1, "\n", 1);
	return (0);
}