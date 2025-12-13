/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_impact_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:29:02 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/10 12:07:48 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_init_ray(t_data *info)
{
	int		i;
	double	angle;
	double	fov;

	fov = FOV * M_PI / 180;
	angle = info->player.angle * M_PI / 180;
	i = 0;
	while (i < WIDTH)
	{
		info->player.ray[i].angle = angle -(fov / 2) \
			+ ((fov / WIDTH) * i);
		info->player.ray[i].angle_ret = info->player.ray[i].angle;
		if (info->player.ray[i].angle < 0)
			info->player.ray[i].angle += 2 * M_PI;
		i++;
	}
}

void	ft_impact_ver(t_ray *ray)
{
	if (ray->ray_dir_x > 0 && ray->ray_dir_y >= 0)
		ray->pixel_width_impact = (ray->hit - ray->map_y) * WIDTH;
	else if (ray->ray_dir_x <= 0 && ray->ray_dir_y > 0)
		ray->pixel_width_impact = (ray->hit - ray->map_y) * WIDTH;
	else if (ray->ray_dir_x >= 0 && ray->ray_dir_y < 0)
		ray->pixel_width_impact = (ray->hit - ray->map_y) * WIDTH;
	else if (ray->ray_dir_x < 0 && ray->ray_dir_y <= 0)
		ray->pixel_width_impact = (ray->hit - ray->map_y) * WIDTH;
}

void	ft_impact_hor(t_ray *ray)
{
	if (ray->ray_dir_x > 0 && ray->ray_dir_y >= 0)
		ray->pixel_width_impact = (ray->hit - ray->map_x) * WIDTH;
	else if (ray->ray_dir_x <= 0 && ray->ray_dir_y > 0)
		ray->pixel_width_impact = (ray->hit - ray->map_x) * WIDTH;
	else if (ray->ray_dir_x >= 0 && ray->ray_dir_y < 0)
		ray->pixel_width_impact = (ray->hit - ray->map_x) * WIDTH;
	else if (ray->ray_dir_x < 0 && ray->ray_dir_y <= 0)
		ray->pixel_width_impact = (ray->hit - ray->map_x) * WIDTH;
}
