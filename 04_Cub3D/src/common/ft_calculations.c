/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:24:12 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:40:02 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_get_size_map(t_map *map)
{
	int	cols;
	int	rows;

	cols = 0;
	rows = 0;
	if (!map->map)
		return ;
	while (map->map[cols])
	{
		if ((int)ft_strlen(map->map[cols]) > rows)
			rows = ft_strlen(map->map[cols]);
		cols++;
	}
	map->map_size_x = rows;
	map->map_size_y = cols;
}

void	ft_get_ang(t_data *info, char dir)
{
	if (dir == 'N')
		info->player.angle = 270;
	if (dir == 'S')
		info->player.angle = 90;
	if (dir == 'E')
		info->player.angle = 0;
	if (dir == 'W')
		info->player.angle = 180;
}

void	ft_get_player_to_wall(t_data *info, t_ray *ray)
{
	if (ray->ray_dir_x > 0)
		ray->side_dist_x = (info->player.map_x + \
			ray->step_x - info->player.pos_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (info->player.pos_x - \
			info->player.map_x) * ray->delta_dist_x;
	if (ray->ray_dir_y > 0)
		ray->side_dist_y = (info->player.map_y + \
			ray->step_y - info->player.pos_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (info->player.pos_y - \
			info->player.map_y) * ray->delta_dist_y;
}

void	ft_vert_cal(t_data *info, t_ray *ray)
{
	double	angle;
	double	player;	

	player = info->player.angle * (M_PI / 180);
	angle = fabs(ray->angle_ret - player);
	if (angle > M_PI)
		angle = 2 * M_PI - angle;
	ray->ver_distance = ray->hyp_distance * cos(angle);
	if (ray->ver_distance < 0.0001)
		ray->ver_distance = 9999999999999.0;
}

void	ft_hipo_cal(t_ray *ray)
{
	if (ray->flag == 0 && ray->ray_dir_x > 0)
		ray->hyp_distance = sqrt(pow((ray->map_x - \
			ray->pos_x), 2) + pow((ray->hit - ray->pos_y), 2));
	else if (ray->flag == 0 && ray->ray_dir_x < 0)
		ray->hyp_distance = sqrt(pow(((ray->map_x + 1) - \
			ray->pos_x), 2) + pow((ray->hit - ray->pos_y), 2));
	else if (ray->flag == 1 && ray->ray_dir_y > 0)
		ray->hyp_distance = sqrt(pow((ray->hit - \
			ray->pos_x), 2) + pow((ray->map_y - ray->pos_y), 2));
	else
		ray->hyp_distance = sqrt(pow((ray->hit - \
			ray->pos_x), 2) + pow(((ray->map_y + 1) - ray->pos_y), 2));
}
