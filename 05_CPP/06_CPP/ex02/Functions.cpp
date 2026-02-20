/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Functions.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:38:27 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/20 19:33:58 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <iostream>

Base	*generate(void) {
	srand(time(NULL));
	char s = "ABC"[rand() % 3];
	std::cout << "Type: " << s << ", aleatorily generated...." << std::endl;
	switch (s)
	{
	case 'A':
		return new A;
		break;
	case 'B':
		return new B;
		break;
	case 'C':
		return new C;
	default :
		return NULL;
	}
}

void	identify(Base *p) {
	bool casted;

	std::cout << "Identify with Base: *";
	casted = dynamic_cast<A*>(p);
	if (casted) {
		std::cout << "A" << std::endl;
		return ;
	}
	casted = dynamic_cast<B*>(p);
	if (casted) {
		std::cout << "B" << std::endl;
		return ;
	}
	casted = dynamic_cast<C*>(p);
	if (casted) {
		std::cout << "C" << std::endl;
		return;
	}
	if (!casted) {
		std::cout << "unknown" << std::endl;
	}
}

void	identify(Base &p) {
	std::cout << "Identify with Base: &";
	try
	{
		A	&a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A" << std::endl;
	}
	catch(const std::exception& e)
	{
		try
		{
			B	&b = dynamic_cast<B&>(p);
			(void)b;
			std::cout << "B" << std::endl;
		}
		catch(const std::exception& e)
		{
			try
			{
				C	&c = dynamic_cast<C&>(p);
				(void)c;
				std::cout << "C" << std::endl;
			}
			catch(const std::exception& e)
			{
				std::cout << "Unknown" << std::endl;
			}
			
		}
		
	}
}