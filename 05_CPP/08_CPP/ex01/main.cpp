/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:31:52 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/11 19:54:40 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
Span sp = Span(5);
sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);
std::cout << sp.shortestSpan() << std::endl;
std::cout << sp.longestSpan() << std::endl;
return 0;
}

/* int	main() {
	Span sp = Span(20000);

	std::vector<int> numbers;
	for (int i = 1; i < 1000; i++)
		numbers.push_back(i);
	try {
			sp.addRamNumber(5000);
			std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
			std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	} catch (std::exception &e) {
		std::cout << RED << e.what() << RESET << std::endl;
	}
	try {
			sp.addNumbers(numbers.begin(), numbers.end());
			std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
			std::cout << "Longest span: " << sp.longestSpan() << std::endl;
	} catch (std::exception &e) {
				std::cout << RED << e.what() << RESET << std::endl;
	}

	return 0;

} */