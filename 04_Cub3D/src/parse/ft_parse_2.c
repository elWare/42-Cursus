/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:30:27 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:31:05 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_get_map(t_data *info, int fd)
{
	char	*line;
	char	*map;

	line = NULL;
	map = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		printf(RED"Failed reading map line.\n"RESET);
		return (FAILURE);
	}
	map = ft_new_str(line, fd);
	if (!map)
		return (FAILURE);
	map = ft_trim_str(map, "\n");
	if (!map)
	{
		printf(RED"Failed in ft_trim_str.\n"RESET);
		return (FAILURE);
	}
	if (ft_split_map(info, map))
		return (FAILURE);
	return (SUCCESS);
}

char	*ft_new_str(char *c, int fd)
{
	char	*map;

	map = NULL;
	while (c)
	{
		if (!c)
		{
			printf(RED"Failed reading map line.\n"RESET);
			return (NULL);
		}
		map = ft_strjoin_safe(map, c);
		if (!map)
		{
			printf(RED"Failed in ft_strjoin_safe"RESET);
			return (NULL);
		}
		c = get_next_line(fd);
	}
	return (map);
}

int	ft_players_num(char **map)
{
	int	n_players;

	n_players = ft_players_count(map);
	if (n_players == 0)
	{
		printf(RED"Missing player in map.\n"RESET);
		return (FAILURE);
	}
	if (n_players > 1)
	{
		printf(RED"Too may players in map.\n"RESET);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_players_count(char **map)
{
	int	col;
	int	row;
	int	n_players;

	col = 0;
	n_players = 0;
	while (map[col])
	{
		row = 0;
		while (map[col][row])
		{
			if (map[col][row] == 'N' || map[col][row] == 'S'
				|| map[col][row] == 'W' || map[col][row] == 'E')
				n_players++;
			row++;
		}
		col++;
	}
	return (n_players);
}
