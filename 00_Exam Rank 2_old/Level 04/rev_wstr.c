/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:01:02 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/25 10:01:11 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>         // for write

int main(int argc, char *argv[])
{
	int start;              // start of the word
	int end;                // end of the word
	int i = 0;              // index to iterate through the string
		
	if(argc == 2)
	{   
		while(argv[1][i] != '\0')
			i++;
        // For the string "Hello world, from 42 Málaga" i = 29 
		while(i >= 0)
		{
			while( argv[1][i] == '\0' || argv[1][i] == ' ' || argv[1][i] == '\t')
				i--;        // skip spaces, tabs and null characters
			end = i;        // ends at the last character of the word
			while(argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
				i--;
			start = i + 1;	// starts at the first character of the word
			int  flag;		// flag to check if it is the first word
			flag = start;	// flag is the first word
			while(start <= end)
			{
				write (1, &argv[1][start],1);
				start++;		
			}
			if (flag != 0)	// if it is not the first word
				write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
	return (0);
}
