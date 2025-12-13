/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:21:27 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/08 18:07:48 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_del_nl(char *str)
{
	char	*new;

	new = ft_realloc(str, ft_strlen(str));
	if (!new)
		return (NULL);
	return (new);
}

void	ft_del_imgs(t_data *data)
{
	if (data->textures.no_texture)
		mlx_delete_texture(data->textures.no_texture);
	if (data->textures.so_texture)
		mlx_delete_texture(data->textures.so_texture);
	if (data->textures.we_texture)
		mlx_delete_texture(data->textures.we_texture);
	if (data->textures.ea_texture)
		mlx_delete_texture(data->textures.ea_texture);
}

void	ft_free_imgs(t_data *data)
{
	t_texture	t;

	t = data->textures;
	if (t.no_flag)
		free(t.no_path);
	if (t.so_flag)
		free(t.so_path);
	if (t.we_flag)
		free(t.we_path);
	if (t.ea_flag)
		free(t.ea_path);
}

void	ft_error_exit(t_data *info)
{
	if (info->map.map)
		ft_split_free(info->map.map);
	ft_free_imgs(info);
	ft_del_imgs(info);
	exit(FAILURE);
}
