/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 09:14:30 by jumarque          #+#    #+#             */
/*   Updated: 2025/04/22 10:30:41 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef BUFFERSIZE
# define BUFFERSIZE 42
#endif

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (len);
	while(*str)
	{
		len++;
		str++;
	}
	return (len);		
}

char	*ft_strchr(char *str, int c)
{
	if (str == NULL)
		return (NULL);
	if (c == '\0')
		return (&str[ft_strlen(str)]);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*result;
	int		i;
	int 	j;
	
	if (str1 == NULL)
	{
		str1 = (char *)malloc(sizeof(char) * 1);
		if (str1 == NULL)
			return (NULL);
		*str1 = '\0';
	}
	if (str2 == NULL)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
		result[j++] = str1[i++];
	i = 0;
	while (str2[i])
		result[j++] = str2[i++];
	result[j] = '\0';
	free(str1);
	return (result);
}

char	*ft_create(int fd, char *buffer)
{
	char	*tmp_buffer;
	int		fr;
	
	tmp_buffer = (char *)malloc(sizeof(char) * (BUFFERSIZE + 1));
	if (tmp_buffer == NULL)
		return (NULL);
	fr = 1;
	tmp_buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n') && fr > 0)
	{
		fr = read(fd, tmp_buffer, BUFFERSIZE);
		if (fr == -1)
		{
			free(tmp_buffer);
			if (!buffer)
				free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[BUFFERSIZE] = '\0';
		buffer = ft_strjoin(buffer, tmp_buffer);
	}
	free(tmp_buffer);
	return (buffer);
}

char	*ft_getline(char *buffer)
{
	char	*line;
	int i;

	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);	
}

char	*ft_cleanline(char *buffer)
{
	char	*resutl_buff;
	int		i;
	int		j;

	if (buffer == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	i++;
	resutl_buff = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i));
	if (resutl_buff == NULL)
		return (NULL);
	j = 0;
	while (buffer[i])
		resutl_buff[j++] = buffer[i++];
	resutl_buff[j] = '\0';
	free(buffer);
	buffer = NULL;
	return (resutl_buff);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
	if (fd < 0 || BUFFERSIZE <= 0)
	{
		if (buffer != NULL)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);		
	}
	buffer = ft_create(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_getline(buffer);
	buffer = ft_cleanline(buffer);
	return (line);
}