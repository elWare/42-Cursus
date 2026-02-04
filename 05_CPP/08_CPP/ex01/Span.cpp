/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:46:59 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/04 17:34:56 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(uint32_t n) : _maxSize(n), _numbers() {}
Span::Span(const Span &oth) {
	*this = oth;
}
Span	&Span::operator=(const Span &oth) {
	this->_maxSize = oth._maxSize;
	this->_numbers = oth._numbers;
	return (*this);
}

void	Span::addNumber(int n) {
	if (this->_numbers.size() >= this->_maxSize)
		throw Span::MaxSizeException();
	this->_numbers.push_back(n);
}

void	Span::addNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end){
	if (this->_numbers.size() + std::distance(begin, end) > this->_maxSize)
		throw Span::MaxSizeException();
	this->_numbers.insert(_numbers.end(), begin, end);
}

void	Span::addRamNumber(uint32_t amount){
	srand(time(NULL));
	try {
		for (uint32_t i = 0; i < amount; i++)
			this->addNumber(rand());
	} catch (std::exception &e) {
		std::cout << RED << e.what() << RESET << std::endl;
	}
}

int	Span::shortestSpan() {
	std::vector<int> vec = this->_numbers;
	if (vec.size() < 2)
		throw Span::notEnoughNumbersException();
	std::sort(vec.begin(), vec.end());
	int min = vec[1] - vec[0];
	std::vector<int>::iterator it;
	for (it = vec.begin(); it != vec.end() - 1; it++) {
		if (abs(*(it + 1) - *it) < min)
			min = abs(*(it + 1) - *it);
	}
	return min;
}
int	Span::longestSpan() {
	std::vector<int> vec = this->_numbers;
	if (vec.size() < 2)
		throw Span::notEnoughNumbersException();
	int min = *std::min_element(vec.begin(), vec.end());
	int max = *std::max_element(vec.begin(), vec.end());
	return max - min;
}

void Span::printNumbers() {
	std::vector<int> vec = this->_numbers;
	std::vector<int>::iterator it;
	std::cout << "Numbers: ";
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}
const char *Span::notEnoughNumbersException::what() const throw() {
	return "Not enough numbers in the list";
}
const char *Span::MaxSizeException::what() const throw() {
	return "Max size reached";
}
	
Span::~Span() {};