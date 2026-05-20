/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:02:38 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/17 13:17:17 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_atoi(const char *str)
{
	int	numb;
	int	sign;

	numb = 0;
	sign = 1;
	
	while (*str == 32 || (*str >= 9 && *str <=13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		numb = numb * 10 + (*str - '0');
		str++;
	}
	return (numb * sign);
}

void	print_hex(int numb)
{
	if (15 < numb)
	{
		print_hex(numb / 16);
		numb = numb % 16;
	}
	write(1, &"0123456789abcdef"[numb], 1);
}

int     main(int argc, char **argv)
{
    if (argc == 2)                   // If the number of arguments is 2
        print_hex(ft_atoi(argv[1])); // It prints the hexadecimal representation of the number
    write(1, "\n", 1);               // It writes a newline to the standard output
    return (0);                      // It returns 0 to the operating system
}