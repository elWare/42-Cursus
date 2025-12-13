/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:24:37 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:37:28 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_movements(t_data *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_W))
		ft_move_player(info, info->player.angle);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
		ft_move_player(info, info->player.angle + 180);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		ft_move_player(info, info->player.angle - 90);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		ft_move_player(info, info->player.angle + 90);
	if (mlx_is_key_down(info->mlx, MLX_KEY_E))
		info->move = 12;
	if (!mlx_is_key_down(info->mlx, MLX_KEY_E))
		info->move = 4;
}

void	ft_handle_rot(t_data *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		ft_check_angles(&info->player.angle, -3);
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		ft_check_angles(&info->player.angle, 3);
}

void	ft_move_player(t_data *info, double ang)
{
	double			mov_x;
	double			mov_y;

	mov_x = (cos(ang * M_PI / 180) * info->move);
	mov_y = (sin(ang * M_PI / 180) * info->move);
	if (ft_check_next_move(info, 0, mov_y))
	{
		info->player.pos_y += mov_y / 64;
	}
	if (ft_check_next_move(info, mov_x, 0))
	{
		info->player.pos_x += mov_x / 64;
	}
}
