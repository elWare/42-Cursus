/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:00:45 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:40:59 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_get_imgs_info(t_data *info, int *res, int *fd)
{
	char	**split_line;
	int		row;
	int		line;

	split_line = NULL;
	row = 0;
	line = 0;
	while (row < 6)
	{
		if (ft_split_line(&split_line, *fd))
			return (FAILURE);
		line++;
		if (ft_check_text(info, split_line, &row, line))
			*res = FAILURE;
	}
	ft_missing_id(info, fd, row);
	return (*res);
}

void	ft_load_imgs(t_data *info)
{
	info->textures.no_texture = mlx_load_png(info->textures.no_path);
	if (!info->textures.no_texture)
	{
		printf(RED"Failed to load png for NO\n"RESET);
		exit(FAILURE);
	}
	info->textures.so_texture = mlx_load_png(info->textures.so_path);
	if (!info->textures.so_texture)
	{
		printf(RED"Failed to load png for SO\n"RESET);
		exit(FAILURE);
	}
	info->textures.ea_texture = mlx_load_png(info->textures.ea_path);
	if (!info->textures.ea_texture)
	{
		printf(RED"Failed to load png for EA\n"RESET);
		exit(FAILURE);
	}
	info->textures.we_texture = mlx_load_png(info->textures.we_path);
	if (!info->textures.we_texture)
	{
		printf(RED"Failed to load png for WE\n"RESET);
		exit(FAILURE);
	}
}
