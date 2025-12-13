/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:46:41 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/10 12:53:20 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_shoot_ray(t_data *info, t_player *player)
{
	int	i;

	ft_init_ray(info);
	i = 0;
	while (i < WIDTH)
	{
		ft_get_impact_ray(info, &player->ray[i]);
		ft_paint_column(info, &player->ray[i], i);
		i++;
	}
}

void	ft_get_impact_ray(t_data *info, t_ray *ray)
{
	ft_init_values_ray(info, ray);
	ft_get_player_to_wall(info, ray);
	ft_search_wall(info, ray);
	if (ray->flag == 0)
		ray->hit = ray->pos_y + (ray->perp_wall_dist * ray->ray_dir_y);
	else
		ray->hit = ray->pos_x + (ray->perp_wall_dist * ray->ray_dir_x);
	if (ray->flag == 0)
		ft_impact_ver(ray);
	else
		ft_impact_hor(ray);
	ft_hipo_cal(ray);
	ft_vert_cal(info, ray);
}

void	ft_init_values_ray(t_data *info, t_ray *ray)
{
	ray->step_x = 0;
	ray->step_y = 0;
	ray->map_x = info->player.map_x;
	ray->map_y = info->player.map_y;
	ray->pos_x = info->player.pos_x;
	ray->pos_y = info->player.pos_y;
	ray->ray_dir_x = cos(ray->angle);
	ray->ray_dir_y = sin(ray->angle);
	ray->delta_dist_x = 1 / fabs(ray->ray_dir_x);
	ray->delta_dist_y = 1 / fabs(ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	ray->flag = 0;
}

void	ft_search_wall(t_data *info, t_ray *ray)
{
	while (info->map.map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->flag = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->flag = 1;
		}
	}
	if (ray->flag == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + \
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + \
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
}
