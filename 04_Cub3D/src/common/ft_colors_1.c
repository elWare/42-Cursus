/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:51:11 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/08 18:07:39 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_check_colors(char **c)
{
	int	len_c;
	int	comma_n;

	len_c = ft_split_len(c);
	comma_n = ft_check_comma(c);
	if (ft_strcmp(c[0], "C") && ft_strcmp(c[0], "F"))
		return (SUCCESS);
	if (len_c == 2 && comma_n == 2)
		return (SUCCESS);
	printf(RED"Bad number of rgb values\n"RESET);
	return (FAILURE);
}

int	ft_check_colors_num(char **c, int line)
{
	int	flag;
	int	i;
	int	j;

	i = 1;
	flag = SUCCESS;
	if (ft_strcmp(c[0], "F") && ft_strcmp(c[0], "C"))
		return (flag);
	while (c[i])
	{
		j = 0;
		while (c[i][j])
		{
			if (!ft_isdigit(c[i][j]) && c[i][j] != ',')
			{
				ft_error_rgb_num(c, i, j, line);
				flag = FAILURE;
			}
			j++;
		}
		i++;
	}
	return (flag);
}

void	ft_error_color(char **path, int r, int g, int b)
{
	printf(RED"Bad rgb value\n"RESET);
	ft_putstr_fd(path[0], 2);
	ft_putstr_fd(". ", 2);
	if (r > 255 || r < 0)
	{
		ft_putstr_fd("r = ", 2);
		ft_putnbr_fd(r, 2);
		ft_putstr_fd(". ", 2);
	}
	if (g > 255 || g < 0)
	{
		ft_putstr_fd("g = ", 2);
		ft_putnbr_fd(g, 2);
		ft_putstr_fd(". ", 2);
	}
	if (b > 255 || b < 0)
	{
		ft_putstr_fd("b = ", 2);
		ft_putnbr_fd(b, 2);
		ft_putstr_fd(".", 2);
	}
	ft_putstr_fd("\n", 2);
}

uint32_t	ft_rgba(uint8_t pixels[4])
{
	uint32_t	c;

	c = 0;
	c |= ((uint32_t)pixels[0] << 24);
	c |= ((uint32_t)pixels[1] << 16);
	c |= ((uint32_t)pixels[2] << 8);
	c |= pixels[3];
	return (c);
}
