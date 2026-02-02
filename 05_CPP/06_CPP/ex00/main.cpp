/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:06:56 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/02 13:16:38 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

using std::cerr; using std::cout; using std::endl;

int main(int argc, char **argv) {
	if (argc != 2 || !argv[1][0]) {
		cerr << RED << "Error" << RESET << ": Invalid arguments" << endl;
		cerr << GREEN << "Usage" << RESET": ./convert [value]" << endl;
		return 1;
	}

	cout << BLUE << "\n* * * Scalar Converter * * *" << RESET << endl;
	ScalarConverter::convert(argv[1]);

	cout << BLUE << "\n* * * * your results * * * *\n" << RESET << endl;
	return 0;
}
