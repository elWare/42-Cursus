/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:25:59 by jumarque          #+#    #+#             */
/*   Updated: 2025/09/09 09:12:33 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBC_H
# define VBC_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

typedef struct	s_node
{
	enum
	{
		ADD,
		MULTI,
		VAL
	} type;
	int	val;
	struct s_node	*l;
	struct s_node	*r;
}	node;

// Coding
node	*parse_expression(char **s);
node	*parse_addition(char **s);
node	*parse_multiplication(char **s);
node	*parse_primary(char **s);
//code given
node	*new_node(node n);
void	destroy_tree(node *n);
int		eval_tree(node *tree);
void	unexpected(char c);
int		accept(char **s, char c);
int		expect(char **s, char c);

#endif
