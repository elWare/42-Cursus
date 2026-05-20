/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:32:37 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/16 09:34:32 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	*ft_rrange(int start, int end)
{
	int step, i = 0;
	int *array;
	int range = (abs(end - start) + 1);

	step = 1;
	array = (int *)malloc(range * sizeof(int));
	if (array == NULL)
		return (NULL);
	if (start > end)
		step = -1;
	i = range - 1;
	while (i >= 0)
	{
			array[i] = start;
			start+=step;
			i--;
	}
	return (array);
}


int main (int argc, char *argv[])
{
    int *res;
    int *original_res;
    int start;
    int end;

    if (argc == 3)
    {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
        res = ft_rrange(start, end);
        original_res = res; 
        // Save the pointer to the first element of the array
        if (start <= end)
        {
            while (start <= end)
            {
                printf("%d\n", *res);
                res++;
                start++;
            }
        }
        else
        {
            while (start >= end)
            {
                printf("%d\n", *res);
                res++;
                start--;
            }
        }
        free(original_res);
        // Free the memory allocated by malloc in the ft_range function
    }
    return (0);
}