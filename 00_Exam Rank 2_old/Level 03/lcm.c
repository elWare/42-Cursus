/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:17:01 by jumarque          #+#    #+#             */
/*   Updated: 2024/12/17 12:17:04 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int gcd(int a, int b)
{
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static int ft_abs(int a, int b)
{
    if (a < 0 || b < 0)
        return (-1 * a * b);
    else
        return (a * b);
}

int lcm(unsigned int a, unsigned int b) 
{
    return (ft_abs(a,b) / gcd(a, b));
}

#include <stdio.h> // printf
#include <stdlib.h> // atoi

int main(int argc, char *argv[])
{
    unsigned int a; // First number
    unsigned int b; // Second number
    unsigned int res; // Result of the operation

    if (argc == 3) // If the number of arguments is 3
    {
        a = atoi(argv[1]); // It converts the first argument to an integer
        b = atoi(argv[2]); // It converts the second argument to an integer
        res = lcm(a, b); // It calculates the least common multiple of a and b
        printf("%d\n", res); // It prints the result to the standard output
    }
    return (0); // It returns 0 to the operating system
}