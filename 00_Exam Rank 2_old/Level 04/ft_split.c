/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:44:36 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/25 09:33:08 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	ft_interword(char c)
{
	return (c == ' ' || c == '\n' || c == 9);
}

int	ft_countwords(char *str)
{
	int	wc = 0,i = 0;

	while(str[i])
	{
		while(str[i] && ft_interword(str[i]))
			i++;
		if (str[i])
			wc++;
		while(str[i] && !ft_interword(str[i]))
			i++;
	}
	return (wc);
}

void ft_strlcpy(char *dst, char *src, int size)
{
	int i = 0;
	
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[size] = '\0';
}

char	**ft_split(char *str)
{
	char	**ptr_split;
	int		words, i = 0, j = 0, k = 0;
	
	if (str)
	{
		words = ft_countwords(str);
		ptr_split = (char **)malloc(sizeof(char **)*(words + 1));
		if (ptr_split == NULL)
			return (NULL);
		while (str[i])
		{
			//Buscar la palabra
			while (str[i] && ft_interword(str[i]))
				i++;
			j = i;
			while (str[i] && !ft_interword(str[i]))
				i++;
			if (i > j)
			{
				ptr_split[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
				if (ptr_split[k] == NULL)
					return (NULL);
				ft_strlcpy(ptr_split[k], &str[j], i - j);
				k++;
			}
			
		}
	}
	ptr_split[k]=NULL;
	return (ptr_split);
}

// esto es para probrar la función

int main (int argc, char *argv[])
{
    if (argc == 1)
        return 0;

    char *str = argv[1];
    char **words = ft_split(str);
    int i = -1;

    while (words[++i])
        printf("%s\n", words[i]);
    return 0;
}
