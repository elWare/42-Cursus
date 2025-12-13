/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:00:55 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:32:06 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_check_cub_ext(char *file, int *i)
{
	char	*c;

	if (!file)
		return (FAILURE);
	c = ft_strchr(file, '.');
	if (!c || ft_len(c) != 4 || ft_strcmp(c, ".cub"))
	{
		printf(RED"Bad extension"RESET" must be .cub\n");
		*i = FAILURE;
	}
	return (*i);
}

int	ft_check_extra(char *map)
{
	int	i;

	i = 0;
	if (!map || !map[0] || map[0] == '\n')
	{
		printf(RED"The map is missing.\n"RESET);
		return (FAILURE);
	}
	while (map[i])
	{
		if (map[i] == '\n')
		{
			i++;
			while (map[i] != '\0' && map[i] == ' ')
				i++;
			if (map[i] == '\n')
			{
				printf(RED"Extra line in map.\n"RESET);
				return (FAILURE);
			}
		}
		if (map[i] != '\0')
			i++;
	}
	return (SUCCESS);
}

int	ft_check_first_last(t_data *info, char **map)
{
	if (ft_check_line_file(map, 1))
		return (FAILURE);
	if (ft_check_line_file(map, info->map.map_line))
		return (FAILURE);
	return (SUCCESS);
}

int	ft_check_inside(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_check_wrongs(map[i][j]))
			{
				ft_bad_letter(map, i, j);
				return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_check_wrongs(char c)
{
	if (c != 'N' && c != 'S' && c != 'W'
		&& c != 'E' && c != ' ' && c != '1'
		&& c != '0' && c != '\n')
	{
		return (FAILURE);
	}
	return (SUCCESS);
}
