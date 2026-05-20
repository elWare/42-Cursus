/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:12:35 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/11 12:24:11 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int main(int argc, char *argv[]){
	if (argc != 4)
		return (1);
	t_life	life;
	life.w = atoi(argv[1]);
	life.h = atoi(argv[2]);
	life.iter = atoi(argv[3]);

	life.board = ft_newboard(life.w, life.h);
	ft_loadboard(life);
	ft_playlife(life);
	ft_printboard(life);
	ft_free(life.board, life.w, life.h);
	return (0);
}