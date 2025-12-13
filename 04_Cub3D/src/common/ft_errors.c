/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:37:46 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/11 18:39:28 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_bad_letter(char **map, int line, int i)
{
	printf(RED"Bad character\n"RESET);
	ft_putchar_fd(map[line][i], 2);
	ft_putstr_fd(" in map at line ", 2);
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(i + 1, 2);
	ft_putstr_fd(".\n", 2);
}

void	ft_error_border(int line, int flag)
{
	if (flag == 1)
	{
		printf(RED"The left side of the map is not closed.\n"RESET);
		printf(RED"Error at line\n"RESET);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(".\n", 2);
	}
	if (flag == 2)
	{
		printf(RED"The right side of the map is not closed.\n"RESET);
		printf("Error.");
		ft_putnbr_fd(line, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	ft_error_bad_spc(int line, int i)
{
	printf(RED"Invalid space.\n"RESET);
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(i + 1, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_error_rgb_num(char **rgb, int i, int j, int line)
{
	printf(RED"Bad argument\n" RESET);
	ft_putchar_fd(rgb[i][j], 2);
	ft_putstr_fd("Line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(". \n", 2);
}
