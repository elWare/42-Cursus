/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:17:18 by jumarque          #+#    #+#             */
/*   Updated: 2025/04/22 11:56:21 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_strjoin(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!str1)
	{
		str1 = (char *)malloc(sizeof(char) * 1);
		str1[0] = '\0';
	}
	if (!str2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)+ 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
		str[j++] = str1[i++];
	i = 0;
	while (str2[i])
		str[j++] = str2[i++];
	str[j] = '\0';
	free(str1);
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while(*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*ft_create(int fd, char *buffer)
{
	char	*tmp_buff;
	ssize_t	fr;

	tmp_buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp_buff)
		return (NULL);
	fr = 1;
	while(!(ft_strchr(tmp_buff, '\n')) && fr > 0)
	{
		fr = read(fd, tmp_buff, BUFFER_SIZE);
		if (fr == -1)
		{
			free (tmp_buff);
			free (buffer);
			return (NULL);
		}
		tmp_buff[fr] = '\0';
		buffer = ft_strjoin(buffer, tmp_buff);
	}
	free(tmp_buff);
	tmp_buff = NULL;
	return (buffer);
}

char	*ft_getline(char *buffer)
{
	char	*line;
	int		index;

	index = 0;
	if (!buffer[index])
		return (NULL);
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (buffer[index] == '\n')
		index++;
	line = malloc(sizeof(char) * (index + 1));
	if (!line)
		return (NULL);
	index = 0;
	while (buffer[index] && buffer[index] != '\n')
	{
		line[index] = buffer[index];
		index ++;
	}
	if(buffer[index] == '\n')
		line[index++] = '\n';
	line[index] = '\0';
	return (line);
}

char	*ft_cleanline(char *buffer)
{
	char	*r_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	r_buffer = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!r_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		r_buffer[j++] = buffer [i++];
	r_buffer[j] = '\0';
	free(buffer);
	buffer = NULL;
	return (r_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		if (!buffer)
			free(buffer);
		line = NULL;
		return (NULL);
	}
	buffer = ft_create(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_getline(buffer);
	buffer = ft_cleanline(buffer);
	return (line);
}