/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:22:47 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/08 12:16:40 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int	ft_rgb_get(char **c)
{
	unsigned int	rgb;

	if (ft_split_len(c) == 2)
	{
		rgb = ft_rgb_to_hex_split(c);
		if (rgb == FAILURE)
			rgb = RGB_ERROR;
	}
	if (ft_split_len(c) == 4)
	{
		rgb = ft_rgb_to_hex(c);
		if (rgb == FAILURE)
			rgb = RGB_ERROR;
	}
	return (rgb);
}

unsigned int	ft_rgb_to_hex_split(char **c)
{
	int				r;
	int				g;
	int				b;
	unsigned int	hex;
	char			**rgb;

	rgb = ft_split(c[1], ',');
	if (!rgb || ft_split_len(rgb) != 3)
	{
		printf(RED"Invalid RGB format\n"RESET);
		ft_split_free(rgb);
		return (FAILURE);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_split_free(rgb);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
	{
		ft_error_color(c, r, g, b);
		return (FAILURE);
	}
	hex = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (hex);
}

unsigned int	ft_rgb_to_hex(char **c)
{
	int				r;
	int				g;
	int				b;
	unsigned int	hex;

	if (!c || !c[0] || !c[1] || !c[2] || !c[3])
		return (FAILURE);
	r = ft_atoi(c[1]);
	g = ft_atoi(c[2]);
	b = ft_atoi(c[3]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
	{
		ft_error_color(c, r, g, b);
		return (FAILURE);
	}
	hex = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (hex);
}

uint32_t	ft_color_wall(t_data *info, t_ray *ray, double size)
{
	uint32_t	c;

	if (ray->flag == 0)
	{
		if (ray->ray_dir_x > 0)
			c = ft_get_color(ray->hit \
				- (int)ray->hit, size, info->textures.ea_texture);
		if (ray->ray_dir_x < 0)
			c = ft_get_color(ray->hit \
				- (int)ray->hit, size, info->textures.we_texture);
		return (c);
	}
	else if (ray->flag == 1)
	{
		if (ray->ray_dir_y > 0)
			c = ft_get_color(ray->hit \
				- (int)ray->hit, size, info->textures.so_texture);
		if (ray->ray_dir_y < 0)
			c = ft_get_color(ray->hit \
				- (int)ray->hit, size, info->textures.no_texture);
		return (c);
	}
	return (0x33333388);
}

uint32_t	ft_get_color(double x, double size, mlx_texture_t *txt)
{
	unsigned int	i;
	uint32_t		index;
	uint8_t			rgba[4];

	i = 0;
	if (!txt || !txt->pixels || x >= 1 || size >= 1)
		return (0);
	index = ((uint32_t)(txt->height * size) * txt->width
			+ (uint32_t)(txt->width * x)) * txt->bytes_per_pixel;
	while (i < 4)
	{
		rgba[i] = txt->pixels[index + i];
		i++;
	}
	return (ft_rgba(rgba));
}
