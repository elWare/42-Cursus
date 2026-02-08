/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:49:13 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/08 12:51:29 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static int evil(const std::string &error) {
	std::cerr << RED << ERROR_MSG << " " << error << RESET << std::endl;		// print error message
	exit(EXIT_FAILURE);												// exit with failure status code 1
}

int main(int argc, char *argv[]) {

	if (argc != 2)									// if the number of arguments is different from 2
		return evil(ERROR_ARG);						// print error message and exit with failure status code 1

	if (!RPN::validExpression(argv[1]))				// if the expression is invalid
		return evil(ERROR_EXP);						// print error message and exit with failure status code 1

	std::cout << "\n" << BLUE;
	std::cout << "==================" << std::endl;
	std::cout << " |@@@@----@|--@@| " << std::endl;
	std::cout << " |@@@----@@|--@@| " << std::endl;
	std::cout << " |@@----@@@|--@@| " << std::endl;
	std::cout << " |@----@@@@|--@@| " << std::endl;
	std::cout << " |@@@@@----|@--@| " << std::endl;
    std::cout << " |@@@@----@|@--@| " << std::endl;
	std::cout << "==================\n" << RESET << std::endl;

	try {
		std::cout << "Result: " << GREEN << RPN::calculator(argv[1]) 
		<< RESET << std::endl << std::endl;					// print the result
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl << std::endl;			// print the exception message
	}

	return EXIT_SUCCESS;							// exit with success status code 0

}
