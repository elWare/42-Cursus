/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:03:19 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/08 13:03:34 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

const char	*RPN::invalidExpression::what() const throw(){
	return (RED "Error: invalid expression, no result." RESET);
}
const char	*RPN::zeroDivision::what() const throw() {
	return (RED "Error: zero divided" RESET);
}

RPN::RPN() {
	std::cout << BLUE "Default constructor calle" << RESET << std::endl;
}

RPN::RPN(const RPN &oth){
	*this = oth;
}

RPN	RPN::operator=(const RPN &oth){
	(void)oth;
	return (*this);
}

RPN::~RPN() {
	std::cout << BLUE "Bye, Destructor called." RESET << std::endl;
}

static int	ft_stoi(const std::string &str) {
	int n;
	std::stringstream	ss(str);
	ss >> n;
	return (n);
}


bool	RPN::validExpression(const std::string &expr) {
	std::stringstream ss(expr);
	std::string tk;
	int	numCount = 0, opCount = 0;

	while (ss >> tk){
		if (tk.find_first_not_of("0123456789") == std::string::npos)
			numCount++;
		else if (tk == "+" || tk =="-" || tk == "*" || tk =="/") {
			opCount++;
			if (numCount < 2)
				return (false);
			numCount--;
		}
		else
			return (false);
	}
	return (numCount == 1 && opCount > 0);
}

long long	RPN::calculator(const std::string &expr) {
	int	left = 0, right = 0, res = 0;
	std::stack<int> tmp;
	std::stringstream nextOne(expr);
	std::string tk;
	
	while (nextOne >> tk) {
		if (tk == "+" || tk =="-" || tk == "*" || tk =="/"){
			if (tmp.size() < 2) 
				throw invalidExpression();
			right = tmp.top();
			tmp.pop();
			left = tmp.top();
			tmp.pop();
			switch (tk[0]) {
			case '+':
				res = left + right;
				break;
			case '-':
				res = left - right;
				break;
			case '*':
				res = left * right;
				break;
			case '/':
				if (right == 0)
					throw zeroDivision();
				res = left / right;
				break;
			default:
				throw invalidExpression();
			}
			tmp.push(res);
		}
		else
			tmp.push(ft_stoi(tk));
	}
	if (tmp.size() != 1)
		throw invalidExpression();
	return (tmp.top());
}