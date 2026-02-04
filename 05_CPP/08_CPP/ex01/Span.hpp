/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:44:03 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/04 17:20:54 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdint.h>
#include <vector>

#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

class Span {
	private:
		uint32_t	_maxSize;
		std::vector<int>	_numbers;
		Span();
	public:
		Span(uint32_t n);
		Span(Span const &oth);
		Span &operator=(Span const &oth);
		~Span();

		void addNumber(int n);
		void addNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end);
		void addRamNumber(uint32_t amount);
		int shortestSpan();
		int longestSpan();
		void printNumbers();
		class notEnoughNumbersException : public std::exception {
			public:
				const char *what() const throw();
		};

		class MaxSizeException : public std::exception {
			public:
				const char *what() const throw();
		};
		
};