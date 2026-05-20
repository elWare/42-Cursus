/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 10:58:46 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/11 12:20:25 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIFE_H
# define LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_life
{
	int		**board;
	int		w;
	int		h;
	int		iter;
} t_life;


int		**ft_newboard(int w, int h);
void	ft_loadboard(t_life var_life);
void	ft_playlife(t_life var_life);
void	ft_printboard(t_life var_life);
void	ft_free(int **board, int w, int h);

#endif