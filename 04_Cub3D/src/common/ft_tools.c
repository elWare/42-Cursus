/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:11:34 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/08 18:07:57 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_split_line(char ***c, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		printf(RED"Failed reading the line.\n"RESET);
		return (FAILURE);
	}
	*c = ft_split_ws(line);
	if (!c)
	{
		printf(RED"Failed in ft_split.\n"RESET);
		free(line);
		return (FAILURE);
	}
	free(line);
	return (SUCCESS);
}

void	ft_new_fd(t_data *info, int row, int *fd)
{
	int		missing_lines;
	int		k;
	char	*str_line;

	k = 0;
	missing_lines = ft_missing_num(info);
	if (missing_lines != 0)
	{
		close(*fd);
		*fd = open(info->file, O_RDONLY);
		if (*fd < 0)
			printf(RED"Failed to poen the map file."RESET);
		else
		{
			while (k <= row - missing_lines)
			{
				str_line = get_next_line(*fd);
				if (str_line && ft_strcmp(str_line, "\n"))
					k++;
				free(str_line);
			}
		}
	}
}

char	*ft_trim_str(char *s1, char *set)
{
	char	*new;

	new = ft_strtrim(s1, set);
	if (s1)
		free(s1);
	return (new);
}

int	ft_split_map(t_data *info, char *map)
{
	if (ft_check_extra(map))
	{
		free(map);
		return (FAILURE);
	}
	info->map.map = ft_split(map, '\n');
	free(map);
	if (!info->map.map)
	{
		printf(RED"Faile in ft_split at ft_split_map function.\n"RESET);
		return (FAILURE);
	}
	info->map.map_line = ft_split_len(info->map.map);
	return (SUCCESS);
}
