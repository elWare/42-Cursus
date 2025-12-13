/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:09:47 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/09 11:17:48 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	info;

	if (argc != 2)
	{
		printf(RED"Bad number of arguments\n");
		printf(BLUE"Usage: ./cub3d map.cub\n"RESET);
		return (1);
	}
	ft_var_setup(&info);
	if (ft_parse(argv[1], &info))
	{
		ft_error_exit(&info);
		return (FAILURE);
	}
	ft_load_imgs(&info);
	ft_start(&info);
	ft_split_free(info.map.map);
	ft_free_imgs(&info);
	ft_del_imgs(&info);
	return (SUCCESS);
}
