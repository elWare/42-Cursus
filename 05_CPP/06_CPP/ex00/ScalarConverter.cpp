/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:35:43 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/19 09:17:32 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

static int ft_atoi(const std::string &str);
static float ft_atof(const std::string &str);
static double ft_atod(const std::string &str);
static bool isChar(const std::string &input);
static bool isInt(const std::string &input);
static bool isFloat(const std::string &input);
static bool isDouble(const std::string &input);
static bool isPseudo(const std::string &input);
static Type getType(const std::string &input);
static void printChar(char c);
static void printInt(int i);
static void printFloat(float f);
static void printDouble(double d);
static void pseudo(Type destType, const std::string &pseudoInput);

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

using std::cout; using std::endl; using std::cerr;

static int	ft_atoi(const std::string &str) {
	char	*end;
	errno = 0;
	long int_num;
	
	int_num = std::strtol(str.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE
		|| int_num < std::numeric_limits<int>::min()
		|| int_num > std::numeric_limits<int>::max()) {
		std::cerr << RED << "Error" << RESET << ":out of range." << std::endl;
		exit(1);
	}
	return static_cast<int>(int_num);
}

static float	ft_atof(const std::string &str) {
	char	*end;
	float	f_num;
	
	errno = 0;
	f_num = std::strtof(str.c_str(), &end);
	if (*end != 'f' || errno == ERANGE) {
		std::cerr << RED << "Error" << RESET << ": out of range." << std::endl;
		return 0.00f;
	}
	return f_num;
}

static double	ft_atod(const std::string &str) {
	char	*end;
	double	d_num;

	errno = 0;
	d_num = std::strtod(str.c_str(), &end);
	if (*end != '\0' || errno == ERANGE) {
		std::cerr << RED << "Error" << RESET << ": out of range." << std::endl;
		return 0.00;
	}
	return d_num;
}

static bool	isChar(const std::string &input) {
	if (input.length() != 1)
		return false;
	if (input.at(0) < std::numeric_limits<char>::min()
		|| input.at(0) > std::numeric_limits<char>::max()
		|| isdigit(input.at(0)))
		return false;
	return true;
}

static bool isInt(const std::string &input) {
	for (size_t i = input.at(0) == '-' ? 1 : 0; i < input.length(); i++) {
		if (!isdigit(input.at(i)))
			return false;
	}
	return true;
}

static bool isFloat(const std::string &input) {
	bool point = false;
	if (input == "-inff" || input == "+inff" || input == "nanf")
		return true;
	if (input.at(input.length() - 1) != 'f')
		return false;
	for (size_t i = 0; i < input.length() - 1; i++) {
		if (input.at(i) == '.' && point)
			return false;
		else if (input.at(i) == '.') {
			point = true;
			continue;
		}
		if (!isdigit(input.at(i)) && input.at(i) != '-' && input.at(i) != '+')
			return false;
	}
	return true;
}

static bool isDouble(const std::string &input) {
	bool point = false;
	if (input == "-inf" || input == "+inf" || input == "nan")
		return true;
	for (size_t i = 0; i < input.length(); i++) {
		if (input.at(i) == '.' && point)
			return false;
		else if (input.at(i) == '.') {
			point = true;
			continue;
		}
		if (!isdigit(input.at(i)) && input.at(i) != '-' && input.at(i) != '+')
			return false;
	}
	return true;
}

static bool isPseudo(const std::string &input) {
	return (input == "-inff" || input == "+inff" || input == "nanf"
	|| input == "-inf" || input == "+inf" || input == "nan");
}

Type getType(const std::string &input) {
	if (isChar(input))
		return CHAR;
	if (isInt(input))
		return INT;
	if (isFloat(input))
		return FLOAT;
	if (isDouble(input))
		return DOUBLE;
	return ERROR;
}

static void printChar(char c) {
	cout << "char: '" << c << "'" << endl;
	cout << "int: " << static_cast<int>(c) << endl;
	cout << "float: " << static_cast<float>(c) << ".00f" << endl;
	cout << "double: " << static_cast<double>(c) << ".00" << endl;
}

static void printInt(int i) {
	if (i >= std::numeric_limits<char>::min() && i <= std::numeric_limits<char>::max()
	&& isprint(static_cast<unsigned char>(i)))
		cout << "char: '" << static_cast<char>(i) << "'" << endl;
	else
		cout << "char: Non displayable" << endl;
	cout << "int: " << i << endl;
	cout << "float: " << static_cast<float>(i) << ".00f" << endl;
	cout << "double: " << static_cast<double>(i) << ".00" << endl;
}

static void printFloat(float f) {
	if (f <= std::numeric_limits<char>::min()
	|| f >= std::numeric_limits<char>::max()) {
		cerr << RED << "Error" << RESET << ": out of int range !!!" << endl;
		exit(1);
	}
	else {
		if (isprint(f))
			cout << "char: '" << static_cast<char>(f) << "'" << endl;
		else
			cout << "char: Non displayable" << endl;
		cout << "int: " << static_cast<int>(f) << endl;
		cout << "float: " << std::fixed << std::setprecision(2) << f << "f" << endl;
		cout << "double: " << static_cast<double>(f) << endl;
	}
}

static void printDouble(double d) {
	if (d <= std::numeric_limits<char>::min() 
	|| d >= std::numeric_limits<char>::max()) {
		cerr << RED << "Error" << RESET << ": out of range !!!" << endl;
		exit(1);
	}
	else {
		if (isprint(d))
			cout << "char: '" << static_cast<char>(d) << "'" << endl;
		else
			cout << "char: Non displayable" << endl;
		cout << "int: " << static_cast<int>(d) << endl;
		cout << "float: " << static_cast<float>(d) << std::setprecision(1) << "f" << endl;
		cout << "double: " << std::fixed << std::setprecision(1) << d << endl;
	}
}

static void pseudo(Type destType, const std::string &pseudoInput) {
	cout << "char: impossible" << endl;
	cout << "int: impossible" << endl;
	if (destType == FLOAT) {
		cout << "float: " << pseudoInput << endl;
		cout << "double: " << pseudoInput.substr(0, pseudoInput.length() - 1) << endl;
	}
	else if (destType == DOUBLE) {
		cout << "float: " << pseudoInput << "f" << endl;
		cout << "double: " << pseudoInput << endl;
	}
}