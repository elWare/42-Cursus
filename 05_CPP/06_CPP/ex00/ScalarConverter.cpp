/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:35:43 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/02 13:14:32 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::~ScalarConverter() {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &){
	return (*this);
}

void	ScalarConverter::convert(const std::string &input) {
	switch (getType(input))
	{
	case CHAR:
		printChar(input.at(0));
		break;
	case INT:
		printInt(ft_atoi(input));
		break;
	case FLOAT:
		if (isPseudo(input))
			pseudo(FLOAT, input);
		else
			printFloat(ft_atof(input));
		break;
	case DOUBLE:
		if (isPseudo(input))
			pseudo(DOUBLE, input);
		else
			printDouble(ft_atod(input));
		break;
	default:
	std::cout << RED << "Error" << RESET << ": invalid input" << std::endl;
		break;
	}
}