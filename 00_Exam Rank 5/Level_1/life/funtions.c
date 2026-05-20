/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funtions.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 11:35:23 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/10 12:24:59 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int		**ft_newboard(int cols, int rows) {
	int **ptr;

	ptr = malloc(rows * sizeof(int *));
	if (ptr == NULL)
		exit (1);
	for (int i = 0; i < rows; i++) {
		ptr[i] = calloc(cols, sizeof(int));
		if (ptr[i] == NULL)
			exit (1);
	}
	return (ptr);
}

void	ft_loadboard(int **board, int w, int h) {
	int	x = 0, y = 0, pen = 0;
	char c;

	while (read(0, &c, 1) ==1)
	{
		if (c == 'w' && y > 0) {y--;}
		else if (c == 's' && y < h - 1) {y++;}
		else if (c == 'a' && x > 0) {x--;}
		else if (c == 'd' && x < w - 1) {x++;}
		else if (c == 'x') {pen = !pen;}
		if (pen) {board[y][x] = 1; }
	}
}

void	ft_playlife(int **board, int w, int h, int iter) {
	int **next_board = ft_newboard(w, h);

	for (int t = 0; t < iter; t++){
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				int alive = 0;
				for (int di = -1 ; di <= 1; di++){
					for (int dj = -1; dj <= 1; dj++){
						if ((di || dj) && (i + di >= 0) && (i + di < h) && (j + dj >= 0) && (j + dj < w))
							alive += board[i + di][j + dj];
					}
				}
				next_board[i][j] = (board[i][j] && (alive == 2 || alive == 3)) || (!board[i][j] && alive == 3);
			}
		}
			for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) { board[i][j] = next_board[i][j]; }
	}
	ft_free(next_board, w, h);
}

void	ft_showboard(int **board, int w, int h){
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++) {
			putchar(board[i][j] ? '0' : ' ');
		}
		putchar('\n');
	}
}

void	ft_free(int **board, int w, int h) {
	if (board == NULL || *board == NULL)
		return ;
	for (int i = 0; i < h; i++){
		free(board[i]);
	}
	free(board);
	(void)w;
}