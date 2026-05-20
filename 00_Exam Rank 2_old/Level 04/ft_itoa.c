/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:07:08 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/23 08:27:30 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int		ft_leng(int nbr)
{
	int len = 0;
	
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		nbr = nbr * -1;
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

void 	ft_putnbr(char *str, int nbr)
{
	if (nbr > 9)
	{
		ft_putnbr(str - 1, nbr / 10);
	} 
	*str = (nbr % 10) + '0';
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	index;
	char	*s_dup;

	len = 0;
	index = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	s_dup = (char *)malloc(len + 1);
	if (s_dup == NULL)
		return (NULL);
	while (index < len)
	{
		s_dup[index] = s[index];
		index++;
	}
	s_dup[index] = '\0';
	return (s_dup);
}

char	*ft_itoa(int nbr)
{
	int		len, negativo;
	char	*str;

	if (nbr == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = ft_leng(nbr);
	negativo = (nbr < 0) + 1;
	str = malloc((len + negativo) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (nbr >= 0)
		ft_putnbr(str + len - 1,nbr);
	else
	{
		str[0]='-';
		ft_putnbr(str + len,-nbr);
		
	}
	return(str);	
}

int main(int argc, char **argv)
{
	char *ptr;
	
	if (argc == 2)
	{
		ptr = ft_itoa(atoi(argv[1]));
		printf("El número es: %s", ptr);
		free(ptr);
	}
	printf("\n");
	return (0);	
}