/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:17:10 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:34:49 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_paint(t_data *info)
{
	uint32_t	width;
	uint32_t	height;

	width = 0;
	while (width < WIDTH)
	{
		height = 0;
		while (height < HEIGHT)
		{
			if (height < HEIGHT / 2)
				mlx_put_pixel(info->background, width, height++,
					info->textures.c_color);
			else
				mlx_put_pixel(info->background, width, height++,
					info->textures.f_color);
		}
		width++;
	}
}

double	ft_size_wall(t_ray *ray)
{
	double	size;

	if (ray->hyp_distance < ray->ver_distance)
		size = (WIDTH / ray->hyp_distance);
	else
		size = (WIDTH / ray->ver_distance);
	return (size);
}

void	ft_paint_column(t_data *info, t_ray *ray, int x)
{
	int			i;
	int			first;
	int			pixel;
	double		size;
	uint32_t	color;

	i = 0;
	pixel = 0;
	size = ft_size_wall(ray);
	first = ((HEIGHT / 2) - (size / 2));
	if (first < 0)
	{
		pixel = -first;
		first = 0;
	}
	while (i < HEIGHT)
	{
		if (i > first && i < HEIGHT - 1)
		{
			color = ft_color_wall(info, ray, (i - first + pixel) / size);
			mlx_put_pixel(info->walls, x, i, color);
		}
		i++;
	}
}
