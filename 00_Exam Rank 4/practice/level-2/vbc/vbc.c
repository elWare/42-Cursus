/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:17:24 by jumarque          #+#    #+#             */
/*   Updated: 2025/09/16 17:41:56 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
	return (0);
}
// ---------------------------------------------------------------------------

node	*parse_addition(char **str);

node	*parse_primary(char **str)
{
	node	tmp;
	node	*ret;
	
	if (**str == '(')
	{
		(*str)++;
		ret = parse_addition(str);
		if (**str != ')' || !ret)
		{
			unexpected(**str);
			return (NULL);
		}
		(*str)++;
		return (ret);
		
	}
	if (isdigit(**str))
	{
		tmp.type = VAL;
		tmp.val = **str - '0';
		tmp.l = NULL;
		tmp.r = NULL;
		ret = new_node(tmp);
		if (!ret)
			return (NULL);
		(*str)++;
		return (ret);
	}
	unexpected(**str);
		return (NULL);
}

node	*parse_multiplication(char **str)
{
	node	*left;
	node	*right;
	node	tmp;
	
	left = parse_primary(str);
	if (!left)
		return (NULL);
	while (**str == '*')
	{
		(*str)++;
		right = parse_primary(str);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		tmp.type = MULTI;
		tmp.val = 0;
		tmp.l = left;
		tmp.r = right;
		left = new_node(tmp);
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
	}
	return (left);
}

node	*parse_addition(char **str)
{
	node	*left;
	node	*right;
	node	tmp;

	left = parse_multiplication(str);
	if (!left)
		return (NULL);
	while (**str == '+')
	{
		(*str)++;
		right = parse_multiplication(str);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		tmp.type = ADD;
		tmp.val = 0;
		tmp.l = left;
		tmp.r = right;
		left = new_node(tmp);
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
	}
	return (left);
}

node	*parse_expression(char **str)
{
    node	*ret;

	ret = parse_addition(str);
	if (ret == NULL)
		return (NULL);
    if (**str) 
    {
        destroy_tree(ret);
		unexpected(**str);
        return (NULL);
    }
	return (ret);
}

int	main(int argc, char **argv)
{
	char	*input;
	
	if (argc !=2)
		return (1);
	input = argv[1];
	node *tree = parse_expression(&input);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
	return (0);
}