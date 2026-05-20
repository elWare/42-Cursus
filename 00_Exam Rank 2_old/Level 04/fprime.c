/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:02:31 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/25 11:52:15 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	ft_isprime(int num)
{
	int i = 3;
	if (num <= 1)
		return (0);
	if (num == 2)
		return (1);
	if (num % 2 == 0)
		return (0);
	while (i <= (num / 2))
	{
		if (num % i == 0)
			return (0);
		i += 2;
	}	
	return (1);
}

int main(int argc, char **argv)
{
	int numb, i, second = 0;
	
	if (argc == 2)
	{
		numb = atoi(argv[1]);
		if (ft_isprime(numb))
			printf("%d", numb);
		else
		{
			if (numb == 1)
				printf("1");
			else
			{
				i = 2;
				while (numb > 1)
				{
					if (numb % i == 0)
					{
						if (ft_isprime(i) && second)
							printf("*%d", i);
						else if (ft_isprime(i) && !second)
						{
							printf("%d", i);
							second = 1;
						}
						numb = numb / i;
					} 
					else
						i++;
				}
			}
		}
	}
	printf("\n");
	return (0);
}