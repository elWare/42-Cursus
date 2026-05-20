/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:59:53 by jumarque          #+#    #+#             */
/*   Updated: 2025/09/28 14:33:04 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	pid_t	pid;
	int		pipe_fds[2];
	
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(pipe_fds) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		else
		{
			if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
				exit(1);
		}
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(pipe_fds[1]);
		return (pipe_fds[0]);
	}
	else
	{
		close(pipe_fds[0]);
		return (pipe_fds[1]);
	}
}

/* int main()
{
	int fd;
	char buffer[1024];
	ssize_t bytes;

	fd = ft_popen("ls", (char *const []){"pwd", NULL}, 'r');
	if (fd == -1)
		return 1;

	while ((bytes = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes] = '\0';
		printf("%s", buffer);
	}

	close(fd);
	return 0;
}
 */
 // Escribir input a un comando
int main()
{
    int fd;
    
    fd = ft_popen("wc", (char *const []){"wc", "-l", NULL}, 'w');
    if (fd == -1)
        return 1;

    write(fd, "line 1\n", 7);
    write(fd, "line 2\n", 7);
    write(fd, "line 3\n", 7);
    write(fd, "line 3\n", 7);
	write(fd, "line 3\n", 7);
	write(fd, "line 3\n", 7);
	
    close(fd);  // wc mostrará "3"
    return 0;
}
