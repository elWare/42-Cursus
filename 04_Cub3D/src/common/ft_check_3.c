/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:44:44 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:41:24 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_check_spaces(char **map)
{
	int	row;
	int	col;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == '0' || map[row][col] == 'N'
				|| map[row][col] == 'W' || map[row][col] == 'E'
				|| map[row][col] == 'S')
			{
				if (ft_check_spaces_map(map, row, col))
					return (FAILURE);
				if (ft_check_spaces_map_2(map, row, col))
					return (FAILURE);
			}
			col++;
		}
		row++;
	}
	return (SUCCESS);
}

int	ft_check_spaces_map(char **map, int row, int col)
{
	if (row != 0)
	{
		if (map[row - 1][col] == ' ' || !map[row - 1][col])
		{
			ft_error_bad_spc(row - 1, col);
			return (FAILURE);
		}
	}
	if (row != ft_split_len(map))
	{
		if (map[row + 1][col] == ' ' || !map[row + 1][col])
		{
			ft_error_bad_spc(row + 1, col);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	ft_check_spaces_map_2(char **map, int row, int col)
{
	if (col != 0)
	{
		if (map[row][col - 1] == ' ' || !map[row][col - 1])
		{
			ft_error_bad_spc(row, col - 1);
			return (FAILURE);
		}
	}
	if ((size_t)col != ft_strlen(map[row]))
	{
		if (map[row][col + 1] == ' ' || !map[row][col + 1])
		{
			ft_error_bad_spc(row, col + 1);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

void	ft_check_pos_player(t_data *info, char **map)
{
	int		row;
	int		col;
	char	c;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == 'N' || map[row][col] == 'S'
				|| map[row][col] == 'W' || map[row][col] == 'E')
			{
				c = map[row][col];
				info->player.pos_x = col + 0.5;
				info->player.pos_y = row + 0.5;
				info->player.map_x = col;
				info->player.map_y = row;
			}
			col++;
		}
		row++;
	}
	ft_get_ang(info, c);
	ft_init_ray(info);
}
