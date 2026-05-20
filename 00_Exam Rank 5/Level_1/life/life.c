/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:24:09 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/10 12:11:42 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int main(int argc, char **argv)
{
	if (argc != 4) { return (1);}
	
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int iter = atoi(argv[3]);
	
	int **board = ft_newboard(w, h);

	ft_loadboard(board, w, h);
	ft_playlife(board, w, h, iter);
	ft_showboard(board, w, h);

	ft_free(board, w, h);
	
	return (0);
}