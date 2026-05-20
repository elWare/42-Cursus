/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_mirror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:17:32 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/28 11:23:36 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (2);
	else
		return (0);
}

char	ft_mirror(char c, int up)
{
	char	cr;
	
	if (up == 1)
		cr = "zyxwvutsrqponmlkjihgfedcba"[c - 'a'];
	else 
		cr = "ZYXWVUTSRQPONMLKJIHGFEDCBA"[c - 'A'];
	return (cr);
}

int main(int argc, char **argv)
{
	int	up;
	int	i;
	char	c;
	
	up = 0;
	i = 0;
	if (argc == 2)
	{
		while(argv[1][i])
		{
			up = ft_alpha(argv[1][i]);
			if(up)
				c = ft_mirror(argv[1][i], up);
			else
				c = argv[1][i];
			write(1, &c, 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
} 