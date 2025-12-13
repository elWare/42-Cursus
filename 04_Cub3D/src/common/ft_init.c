/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:04:59 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/09 13:38:52 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_imgs_values(t_data *info)
{
	info->textures.c_flag = 0;
	info->textures.f_flag = 0;
	info->textures.no_flag = 0;
	info->textures.so_flag = 0;
	info->textures.we_flag = 0;
	info->textures.ea_flag = 0;
}

void	ft_init_player(t_data *info)
{
	info->player.angle = 0;
	info->player.map_x = 0;
	info->player.map_y = 0;
	info->player.pos_x = 0;
	info->player.pos_y = 0;
}

void	ft_init_imgs(t_data *info)
{
	ft_init_imgs_values(info);
	info->textures.c_color = 0;
	info->textures.f_color = 0;
	info->textures.no_path = NULL;
	info->textures.so_path = NULL;
	info->textures.we_path = NULL;
	info->textures.ea_path = NULL;
	info->textures.no_texture = NULL;
	info->textures.so_texture = NULL;
	info->textures.we_texture = NULL;
	info->textures.ea_texture = NULL;
}

int	ft_var_setup(t_data *info)
{
	ft_init_imgs(info);
	ft_init_player(info);
	info->background = NULL;
	info->file = NULL;
	info->move = 0;
	info->mlx = NULL;
	info->walls = NULL;
	info->map.map = NULL;
	info->map.map_line = 0;
	info->map.map_size_x = 0;
	info->map.map_size_y = 0;
	info->no_first_time = false;
	return (SUCCESS);
}

void	ft_init_walls(t_data *info, mlx_image_t **img)
{
	*img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	if (!*img)
	{
		printf(RED"Error creating floor-ceiling\n"RESET);
		exit(FAILURE);
	}
	if (mlx_image_to_window(info->mlx, *img, 0, 0) == -1)
	{
		printf(RED"Error in mlx_image_to_window() for floor-ceiling\n"RESET);
		exit(FAILURE);
	}
}
