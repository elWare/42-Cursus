/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:44:10 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/02 17:45:25 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_check_sides(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_check_left_file(map[i]))
		{
			ft_error_border(i + 1, 1);
			return (FAILURE);
		}
		if (ft_check_right_file(map[i]))
		{
			ft_error_border(i + 1, 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_check_left_file(char *c)
{
	int	i;

	i = 0;
	while (c[i] == ' ')
		i++;
	if (c[i] != '1')
		return (FAILURE);
	return (SUCCESS);
}

int	ft_check_right_file(char *c)
{
	int	i;

	i = ft_strlen(c);
	i--;
	while (c[i] == ' ')
		i--;
	if (c[i] != '1')
		return (FAILURE);
	return (SUCCESS);
}
