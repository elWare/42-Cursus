/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:24:35 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/19 08:37:57 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <iostream>

#define BLUE "\033[1;34m"
#define GREEN "\033[0;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

enum Type { 
	ERROR,
	PSEUDO,
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
};

class ScalarConverter {
	public:
		static void	convert(const std::string &input);

	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &oth);
		ScalarConverter	&operator=(const ScalarConverter &oth);
		~ScalarConverter();
};
