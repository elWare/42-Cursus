/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:05:19 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/10 12:55:42 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_words(const char *s)
{
	int	num;

	num = 0;
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\n' && *s != '\r'
			&& *s != '\v' && *s != '\f')
		{
			num++;
			while (*s && *s != ' ' && *s != '\t' && *s != '\n' && *s != '\r'
				&& *s != '\v' && *s != '\f')
				s++;
			if (!*s)
				break ;
		}
		s++;
	}
	return (num);
}

static char	*get_next_word(const char **s)
{
	const char	*start;
	const char	*end;

	start = *s;
	while (*start && *start == ' ' && *start == '\t' && *start == '\n'
		&& *start == '\r' && *start == '\v' && *start == '\f')
		start++;
	end = start;
	while (*end && *end != ' ' && *end != '\t' && *end != '\n'
		&& *end != '\r' && *end != '\v' && *end != '\f')
		end++;
	if (start == end)
		return (NULL);
	*s = end;
	return (ft_strndup(start, end - start));
}

char	**ft_split_ws(char const *s)
{
	int		word_num;
	char	**res;
	int		i;

	if (!s)
		return (NULL);
	word_num = num_words(s);
	res = malloc((word_num + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != ' ' && *s != '\t' )
		{
			res[i] = get_next_word(&s);
			if (!res[i])
				break ;
			i++;
		}
		else
			s++;
	}
	res[i] = NULL;
	return (res);
}
