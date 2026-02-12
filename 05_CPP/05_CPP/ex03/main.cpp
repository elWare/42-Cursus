/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:21:44 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/12 15:04:12 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include "AForm.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

using std::cerr; using std::cout; using std::endl;

int main() {

	AForm *a; AForm *b; AForm *c;

	cout << endl;

	Intern Musk;
	cout << endl;

	a = Musk.makeForm("presidential pardon", "Donald");
	cout << endl;

	b = Musk.makeForm("robotomy request", "Donald");
	cout << endl;

	c = Musk.makeForm("shrubbery creation", "Donald");
	cout << endl;
	
	Musk.makeForm("UP2U", "Donald");
	cout << endl;

	delete a; delete b; delete c;

	return 0;
	
}
