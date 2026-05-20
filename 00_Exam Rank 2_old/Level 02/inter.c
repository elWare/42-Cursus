/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:12:49 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/27 13:31:17 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	ft_cleandup(char *str)
{
	int i, j, k;

	if(*str)
	{
		i = 0;
		j = 1;
		while (str[i])
		{
			j = i + 1;
			while(str[j])
			{
				if (str[i] == str[j])
				{
					k = j + 1;
					while (str[k])
					{
						str[k - 1] = str[k];
						k++;
					}
					str[k - 1] = '\0';
				}
				else
					j++;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	int i = 0, j = 0;

	if (argc == 3)
	{
		ft_cleandup(argv[1]);
		ft_cleandup(argv[2]);
		while (argv[1][i] && argv[2][j])
		{
			if (ft_strchr(argv[2], argv[1][i]))
			{
				write(1, &argv[1][i], 1);
			}
			i++;
			j++;
		}
	}
	write(1, "\n", 1);
	return (0);
}