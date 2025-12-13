/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:44:22 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/10 11:51:34 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_start(t_data *info)
{
	ft_play_game(info);
	mlx_loop_hook(info->mlx, ft_callback, info);
	mlx_loop(info->mlx);
	mlx_terminate(info->mlx);
}

void	ft_play_game(t_data *info)
{
	info->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!info->mlx)
	{
		printf(RED"Error initializing mlx.\n"RESET);
		exit(FAILURE);
	}
	ft_init_walls(info, &info->background);
	ft_init_walls(info, &info->walls);
	info->move = 4;
	ft_check_pos_player(info, info->map.map);
	ft_paint(info);
}

void	ft_callback(void	*value)
{
	t_data	*info;

	info = value;
	if (info->no_first_time)
		mlx_delete_image(info->mlx, info->walls);
	else
		info->no_first_time = true;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	ft_movements(info);
	ft_handle_rot(info);
	ft_init_walls(info, &info->walls);
	ft_shoot_ray(info, &info->player);
}
