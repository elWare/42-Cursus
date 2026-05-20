/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:51:16 by jumarque          #+#    #+#             */
/*   Updated: 2025/09/10 14:52:53 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
	pid_t	pid;
	int		pipe_fds[2];
	int		prev_fd;
	int		exit_status;
	int		status;
	int		i;

	status = 0;
	exit_status = 0;
	prev_fd = -1;
	i = 0;
	if (!cmds || !cmds[0]== NULL)
		return (1);
	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(pipe_fds) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
			{
				close(pipe_fds[0]);
				close(pipe_fds[1]);
			}
			return (1);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					exit(1);
				close (prev_fd);
			}
			if (cmds[i + 1])
			{
				close(pipe_fds[0]);
				if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
					exit (1);
				close(pipe_fds[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit (1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds[i + 1])
		{
			close(pipe_fds[1]);
			prev_fd = pipe_fds[0];
		}
		i++;
	}
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		 exit_status = 1;
	}
	return (exit_status);
}

// EJEMPLO DE USO CON MAIN:

#include <stdio.h>
#include <string.h>

static int count_cmds(int argc, char **argv)
{
    int count = 1;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "|") == 0)
            count++;
    }
    return count;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return (fprintf(stderr, "Usage: %s cmd1 [args] | cmd2 [args] ...\n", argv[0]), 1);

    int cmd_count = count_cmds(argc, argv);
    char ***cmds = calloc(cmd_count + 1, sizeof(char **));
    if (!cmds)
        return (perror("calloc"), 1);

    // Parsear argumentos y construir array de comandos
    int i = 1, j = 0;
    while (i < argc)
    {
        int len = 0;
        while (i + len < argc && strcmp(argv[i + len], "|") != 0)
            len++;
        
        cmds[j] = calloc(len + 1, sizeof(char *));
        if (!cmds[j])
            return (perror("calloc"), 1);
        
        for (int k = 0; k < len; k++)
            cmds[j][k] = argv[i + k];
        cmds[j][len] = NULL;
        
        i += len + 1;  // Saltar el "|"
        j++;
    }
    cmds[cmd_count] = NULL;

    int ret = picoshell(cmds);

    // Limpiar memoria
    for (int i = 0; cmds[i]; i++)
        free(cmds[i]);
    free(cmds);

    return ret;
}
