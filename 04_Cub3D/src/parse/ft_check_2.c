/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:12:31 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/09 11:58:42 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_check_imgs(char **c, int line)
{
	if (ft_check_cardinal(c) || ft_check_path(c, line)
		|| ft_check_bad_argument(c) || ft_check_file(c[0], c[1])
		|| ft_check_colors(c) || ft_check_colors_num(c, line))
		return (FAILURE);
	return (SUCCESS);
}

int	ft_check_cardinal(char **c)
{
	if (ft_strcmp(c[0], "NO") && ft_strcmp(c[0], "SO")
		&& ft_strcmp(c[0], "WE") && ft_strcmp(c[0], "EA")
		&& ft_strcmp(c[0], "F") && ft_strcmp(c[0], "C"))
		return (FAILURE);
	return (SUCCESS);
}

int	ft_check_path(char **c, int line)
{
	if (!c[1])
	{
		printf(RED"Bad value KEY: %s in line: %d\n"RESET, c[0], line);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_check_bad_argument(char **c)
{
	if (c && c[2] && ft_strcmp(c[0], "C") && ft_strcmp(c[0], "F")
		&& c[0][0] != 1)
	{
		printf(RED"Extra argument in file\n"RESET);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_check_map_closed(t_data *info)
{
	if (ft_check_first_last(info, info->map.map))
		return (FAILURE);
	if (ft_check_sides(info->map.map))
		return (FAILURE);
	return (SUCCESS);
}
