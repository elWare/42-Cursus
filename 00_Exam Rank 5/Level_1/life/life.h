/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:31:26 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/10 12:24:35 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_loadboard(int **board, int w, int h);
void	ft_playlife(int **board, int w, int h, int iter);
void	ft_showboard(int **board, int w, int h);
int		**ft_newboard(int w, int h);
void	ft_free(int **board, int w, int h);

#endif
