/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:44:58 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/23 18:44:53 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define ARRAYSIZE 3

int	main() {

	std::string array[] = { "Hola ", "Que ", "Tal " };

	std::cout << "\n";
	std::cout << GREEN << "Array before iter:" << RESET << std::endl;
	::iter(array, ARRAYSIZE, &::print<std::string>);
	::iter(array, ARRAYSIZE, &::addItself<std::string>);
	std::cout << "\n";
	std::cout << GREEN << "Array after iter:"<< RESET << std::endl;
	::iter(array, ARRAYSIZE, &::print<std::string>);

	return 0;
}