/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 11:54:33 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/08 12:03:14 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#define BLUE "\033[0;34m"					// blue color
#define GREEN "\033[0;32m"					// dark green color
#define PURPLE "\033[0;35m"					// purple color
#define RED "\033[0;31m"					// red color
#define RESET "\033[0m"						// reset color

#define ERROR_ARG "Invalid number of arguments."
#define ERROR_EXP "Invalid expression."
#define ERROR_MSG "Error:"

class RPN {
	public:
		RPN();
		RPN(const RPN &oth);
		RPN	operator=(const RPN &oth);
		~RPN();
		
		static bool validExpression(const std::string &expr);
		static long long calculator(const std::string &expr);

		class invalidExpression: public std::exception {
			public:
				virtual const char *what() const throw();
		};
		class zeroDivision: public std::exception {
			public:
				virtual const char *what() const throw();
		};
};