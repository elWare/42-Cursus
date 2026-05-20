/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:45:04 by jumarque          #+#    #+#             */
/*   Updated: 2025/09/18 13:03:38 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int	picoshell(char **cmds[])
{
	pid_t	pid[15];
	int		pipe_fd[2];
	int		prev_fd;
	int		exit_status;
	int		status;
	int		i;

	prev_fd = -1;
	exit_status = 0;
	status = 0;
	i = 0;

	if (!cmds || !cmds[0])
		return (1);
	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(pipe_fd) == -1)
			return (1);
		pid[i] = fork();
		if (pid[i] == -1)
		{
			if(cmds[i + 1])
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			return (1);
		}
		if (pid[i] == 0)
		{
			if (prev_fd != -1)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					exit (1);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				close(pipe_fd[0]);
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
					exit (1);
				close(pipe_fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds[i + 1])
		{
			prev_fd = pipe_fd[0];
			close(pipe_fd[1]);
		}
		i++;
	}
	i--;
	while (i >= 0)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_status = 1;
		i--;
	}
	return (exit_status);
}
	/*
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_status = 1;
	}*/
