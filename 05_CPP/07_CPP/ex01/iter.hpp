/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:23:41 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/03 14:43:18 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <string>

template <typename T>
void	iter(T	*array, size_t size, void (*f)(T&)) {
	for (size_t i = 0; i < size ; i++)
		f(array[i]);
}

template <typename T>
void	iter(const T *array, size_t size, void (*f)(const T&))
{
	for (size_t i = 0; i < size; i++)
		f(array[i]);
}

template <typename T>
void	addOne(T &x) {x++;}

template <typename T>
void	print(T &x) {std::cout << x << std::endl;}