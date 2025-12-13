/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:58:15 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/08 12:26:24 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_check_text(t_data *info, char **c, int *row, int line)
{
	int	ret;

	ret = SUCCESS;
	if (!c[0])
	{
		ft_split_free(c);
		return (SUCCESS);
	}
	if (ft_check_imgs(c, line))
		ret = FAILURE;
	ft_add_text_path(info, c);
	ft_split_free(c);
	*row += 1;
	return (ret);
}

void	ft_add_text_path_2(t_data *info, char **c)
{
	if (c[0] && c[1] && !ft_strcmp(c[0], "C") && info->textures.c_flag != 1)
	{
		info->textures.c_color = ft_rgb_get(c);
		if (info->textures.c_color == RGB_ERROR)
			ft_error_exit(info);
		info->textures.c_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "F")
		&& info->textures.f_flag != 1)
	{
		info->textures.f_color = ft_rgb_get(c);
		if (info->textures.f_color == RGB_ERROR)
			ft_error_exit(info);
		info->textures.f_flag = 1;
	}
}

void	ft_add_text_path(t_data *info, char **c)
{
	if (c[0] && c[1] && !ft_strcmp(c[0], "NO") && info->textures.no_flag != 1)
	{
		info->textures.no_path = ft_strdup(c[1]);
		info->textures.no_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "SO")
		&& info->textures.so_flag != 1)
	{
		info->textures.so_path = ft_strdup(c[1]);
		info->textures.so_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "EA")
		&& info->textures.ea_flag != 1)
	{
		info->textures.ea_path = ft_strdup(c[1]);
		info->textures.ea_flag = 1;
	}
	else if (c[0] && c[1] && !ft_strcmp(c[0], "WE")
		&& info->textures.we_flag != 1)
	{
		info->textures.we_path = ft_strdup(c[1]);
		info->textures.we_flag = 1;
	}
	ft_add_text_path_2(info, c);
}

int	ft_check_line_file(char **map, int end)
{
	int	i;

	i = 0;
	while (map[end - 1][i])
	{
		if (map[end - 1][i] != ' ' && map[end - 1][i] != '1')
		{
			printf(RED "Invalid character in the %i line of the map\n" RESET, (i
					+ 1));
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
