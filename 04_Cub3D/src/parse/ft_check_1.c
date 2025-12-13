/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:41:43 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:33:16 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_check_file(char *file, char	*img)
{
	int	fd;

	if (!ft_strcmp(file, "C") || !ft_strcmp(file, "F"))
		return (SUCCESS);
	fd = open(img, O_RDONLY);
	if (fd < 0)
	{
		printf(RED"Failed to open the texture file\n"RESET);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	ft_check_map(t_data *info)
{
	if (!info || !info->map.map)
		return (FAILURE);
	if (ft_check_map_closed(info) || ft_check_inside(info->map.map)
		|| ft_check_spaces(info->map.map) || ft_players_num(info->map.map))
		return (FAILURE);
	return (SUCCESS);
}

void	ft_check_angles(double *ang, double i)
{
	*ang += i;
	if (*ang > 359)
		*ang = 0;
	if (*ang < 0)
		*ang = 359;
}

bool	ft_check_next_move(t_data *info, double mov_x, double mov_y)
{
	if (!ft_check_valid_mov(info, mov_x, mov_y))
		return (0);
	info->player.map_x = info->player.pos_x + mov_x / 64;
	info->player.map_y = info->player.pos_y + mov_y / 64;
	return (1);
}

bool	ft_check_valid_mov(t_data *info, double mov_x, double mov_y)
{
	int	check_x;
	int	check_x2;
	int	check_y;
	int	check_y2;

	check_x = (int)floor((info->player.pos_x + 0.25) + (mov_x / 64));
	check_x2 = (int)floor((info->player.pos_x - 0.25) + (mov_x / 64));
	check_y = (int)floor((info->player.pos_y + 0.25) + (mov_y / 64));
	check_y2 = (int)floor((info->player.pos_y - 0.25) + (mov_y / 64));
	if (info->map.map[check_y][check_x] == '1')
		return (0);
	if (info->map.map[check_y2][check_x] == '1')
		return (0);
	if (info->map.map[check_y][check_x2] == '1')
		return (0);
	if (info->map.map[check_y2][check_x2] == '1')
		return (0);
	return (1);
}
