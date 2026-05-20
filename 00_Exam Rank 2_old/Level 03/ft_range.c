/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:47:57 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/27 09:52:10 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_abs(int numb)
{
	if (numb < 0)
		return (-numb);
	return (numb);
}
int	*ft_range(int start, int end)
{
	int step, i = 0;
	int *array;
	int range = (ft_abs(end - start) + 1);

	step = 1;
	array = (int *)malloc(range * sizeof(int) + 1);
	if (array == NULL)
		return (NULL);
	if (start > end)
		step = -1;
	while (i < range)
	{
			array[i] = start;
			start+=step;
			i++;
	}
	array[range] = '\0';
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