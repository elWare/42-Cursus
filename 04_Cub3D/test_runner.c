/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:57:34 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/11 19:00:50 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1

#define BOLD "\033[1m"
#define BLUE "\x1b[34m"
#define CLEAR "\033[2J"
#define CYAN "\x1b[36m"
#define GREEN "\x1b[32m"
#define GREYM "\x1B[38;5;245m"
#define GREYM2 "\x1B[38;5;250m"
#define MAGENTA "\x1b[35m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define WHITE "\033[37m"
#define YELLOW "\x1b[33m"

int	run_test(const char *map_name)
{
	char	command[256];
	int		result;

	snprintf(command, sizeof(command), "./cub3D %s", map_name);
	result = system(command);
	if (WEXITSTATUS(result) == FAILURE)
	{
		printf(YELLOW"☝️ Test EXIT == 1 for: %s\n"RESET, map_name);
		return (SUCCESS);
	}
	else
	{
		printf(GREEN"☝️ Test EXIT == 0 for: %s\n"RESET, map_name);
		return (FAILURE);
	}
}

int	main(int argc, char **argv)
{
	FILE	*file;
	char	map_name[256];

	if (argc != 2)
	{
		printf(RED"Usage: ./test_runner <list_file>\n"RESET);
		return (FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		printf(RED"Error opening list\n"RESET);
		return (FAILURE);
	}
	while (fgets(map_name, sizeof(map_name), file))
	{
		map_name[strcspn(map_name, "\n")] = 0;
		if (map_name[0] != '\0')
			run_test(map_name);
	}
	fclose(file);
	return (SUCCESS);
}
