/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:28:50 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/18 19:47:25 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(char *str)
{
	int numb = 0;
	while(*str)
	{
		if(*str <= '9' && *str >= '0')
			numb = (numb * 10) + *str - '0';
		str++;
	}
	return (numb);
}

void	ft_printnumber(int numb)
{
	char c;
	
	if (numb > 9)
	{
		ft_printnumber(numb / 10);
	}
	numb = numb % 10;
	c = '0' + numb;
	write (1, &c, 1);
}

void	ft_printtable(int numb)
{
	int i;

	i = 1;
	while (i < 10)
	{
		ft_printnumber(i);
		write(1, " x ", 3);
		ft_printnumber(numb);
		write(1, " = ", 3);
		ft_printnumber(numb * i);
		write(1, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	int numb;
	
	if (argc ==2)
	{
		numb = ft_atoi(argv[1]);
		ft_printtable(numb);
	}
	else
		write(1, "\n", 1);
	return(0);
}