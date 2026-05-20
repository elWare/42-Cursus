/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:44:54 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/17 12:51:51 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	mcd(int a, int b)
{
	int tmp;
	while(b != 0)
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return (a);
}

int	main(int argc, char **argv)
{
	int a = 0 ,b = 0;
	if (argc == 3)
	{
		a = atoi(argv[1]);
		b = atoi(argv[2]);
		printf("El mcd de %d y %d es: %d", a, b,mcd(a,b));
	}
	printf("\n");
	return (0);
}