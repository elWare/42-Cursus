/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:24:35 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/02 13:14:20 by jumarque         ###   ########.fr       */
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



int ft_atoi(const std::string &str);
float ft_atof(const std::string &str);
double ft_atod(const std::string &str);
bool isChar(const std::string &input);
bool isInt(const std::string &input);
bool isFloat(const std::string &input);
bool isDouble(const std::string &input);
bool isPseudo(const std::string &input);
Type getType(const std::string &input);
void printChar(char c);
void printInt(int i);
void printFloat(float f);
void printDouble(double d);
void pseudo(Type destType, const std::string &pseudoInput);
