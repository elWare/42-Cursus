/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:44:58 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/03 14:48:31 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define arraySize 3

int	main() {

	int arrayInt[] = { 1, 10, -100 };

	std::cout << "\n";
	std::cout << GREEN << "arrayInt before iter:" << RESET << std::endl;
	::iter(arrayInt, arraySize, &::print<int>);
	::iter(arrayInt, arraySize, &::addOne<int>);
	std::cout << "\n";
	std::cout << GREEN << "arrayInt after iter:"<< RESET << std::endl;
	::iter(arrayInt, arraySize, &::print<int>);

	return 0;
}