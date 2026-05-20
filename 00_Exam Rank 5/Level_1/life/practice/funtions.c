/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funtions.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:10:03 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/11 12:28:49 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int		**ft_newboard(int w, int h)
{
	int	**ptr;
	
	ptr = malloc(h * sizeof(int **));
	if (ptr == NULL)
		exit (1);	
	for (int rows = 0; rows < h; rows++){
		ptr[rows] = calloc(w, sizeof(int));
		if (ptr[rows] == NULL){
			free(ptr);
			exit (1);
		}
	}
	return (ptr);
}

void	ft_loadboard(t_life var_life){
	int		**ptr_board = var_life.board;
	int		x = 0, y = 0, pen = 0;
	char	c;
	
	while (read(0, &c, 1) == 1) {
		if (c == 'w' && y > 0) {y--;}
		else if (c == 's' && y < var_life.h - 1) {y++;}
		else if (c == 'a' && x > 0) {x--;}
		else if (c == 'd' && x < var_life.w - 1) {x++;}
		else if (c == 'x') {pen = !pen;};
		if (pen) {ptr_board[y][x] = 1;}
	}
}

void	ft_playlife(t_life	life)
{
	int		**next_board = ft_newboard(life.w, life.h);
	int		**board = life.board;

	for (int iter =0 ; iter < life.iter; iter++){
		for (int i = 0; i < life.h; i++){
			for (int j = 0; j < life.w; j++){
				int alive = 0;
				for (int di = -1; di <= 1; di++){
					for (int dj = -1; dj <= 1; dj++){
						if ((di || dj) && (i + di >= 0) && (i + di < life.h) && (j + dj >= 0) && (j + dj < life.w))
							alive += board[i + di][j + dj];
					}
				}
				next_board[i][j] = ((board[i][j] && (alive == 2 || alive == 3)) || (!board[i][j] && alive == 3));
			}
		}
		for (int i = 0; i < life.h; i++){
			for (int j = 0; j < life.w; j++){
				board[i][j] = next_board[i][j];
			}
		}
	}
	ft_free(next_board, life.w, life.h);
}

void ft_printboard(t_life life){
	int **board = life.board;
	
	for (int i = 0; i < life.h; i++){
		for (int j = 0; j < life.w; j++)
		{
			putchar((board[i][j] == 1 ? '0' : ' '));
		}
		putchar('\n');
	}
}

void ft_free (int **board, int w, int h){
	if (board == NULL || *board == NULL)
		return ;
	for (int i = 0; i < h; i++)
		free(board[i]);
	free(board);
	(void)w;
}