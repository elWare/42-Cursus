/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:18:41 by sternero          #+#    #+#             */
/*   Updated: 2025/12/09 12:47:32 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_string_add(char **array, char *str)
{
	int		i;
	char	**new;

	i = 0;
	while (array[i] != NULL)
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		new[i] = array[i];
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
	{
		free(new);
		return (NULL);
	}
	new[i + 1] = NULL;
	free(array);
	return (new);
}
