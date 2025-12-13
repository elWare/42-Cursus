/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:12:06 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/05 11:58:46 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_parse(char *cub, t_data *info)
{
	int	fd;
	int	fault_flag;

	fault_flag = 0;
	if (ft_check_cub_ext(cub, &fault_flag))
		return (FAILURE);
	info->file = cub;
	fd = open(cub, O_RDONLY);
	if (fd < 0)
	{
		printf(RED"Opening the map file failed.\n"RESET);
		return (FAILURE);
	}
	if (ft_get_imgs_info(info, &fault_flag, &fd) || ft_get_map(info, fd)
		|| ft_check_map(info))
	{
		fault_flag = FAILURE;
	}
	close(fd);
	if (fault_flag != FAILURE)
		ft_get_size_map(&info->map);
	return (fault_flag);
}

int	ft_check_comma(char **c)
{
	int	i;
	int	j;
	int	comma_n;

	i = 0;
	comma_n = 0;
	while (c[i])
	{
		j = 0;
		while (c[i][j])
		{
			if (c[i][j] == ',')
				comma_n++;
			j++;
		}
		i++;
	}
	return (comma_n);
}

void	ft_missing_id(t_data *info, int *fd, int row)
{
	ft_new_fd(info, row, fd);
	if (info->textures.c_flag != 1)
		printf(RED"\"C\" identifier error\n"RESET);
	if (info->textures.f_flag != 1)
		printf(RED"\"F\" identifier error\n"RESET);
	if (info->textures.no_flag != 1)
		printf(RED"\"NO\" identifier error\n"RESET);
	if (info->textures.so_flag != 1)
		printf(RED"\"SO\" identifier error\n"RESET);
	if (info->textures.we_flag != 1)
		printf(RED"\"WE\" identifier error\n"RESET);
	if (info->textures.ea_flag != 1)
		printf(RED"\"EA\" identifier error\n"RESET);
}

int	ft_missing_num(t_data *info)
{
	int	missing_lines;

	missing_lines = 0;
	if (info->textures.c_flag != 1)
		missing_lines++;
	if (info->textures.f_flag != 1)
		missing_lines++;
	if (info->textures.no_flag != 1)
		missing_lines++;
	if (info->textures.so_flag != 1)
		missing_lines++;
	if (info->textures.we_flag != 1)
		missing_lines++;
	if (info->textures.ea_flag != 1)
		missing_lines++;
	return (missing_lines);
}
