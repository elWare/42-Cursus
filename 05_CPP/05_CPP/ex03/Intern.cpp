/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42Malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:21:19 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/01 13:21:26 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::Intern() {
	std::cout << "Intern: " << "default constructor" << " called" << std::endl;
}

Intern::Intern(const Intern &src) {
	std::cout << "Intern: " << "copy constructor" << " called" << std::endl;
	*this = src;
}

Intern &Intern::operator=(const Intern &rhs) {
	std::cout << "Intern: " << "assignation operator" << " called" << std::endl;
	if (this == &rhs)
		return *this;
	return *this;
}

Intern::~Intern() {
	std::cout << "Intern: " << "destructor" << " called" << std::endl;
}

static AForm *createPresidentialPardonForm(const std::string target) {
	return new PresidentialPardonForm(target);
}
static AForm *createRobotomyRequestForm(const std::string target) {
	return new RobotomyRequestForm(target);
}
static AForm *createShrubberyCreationForm(const std::string target) {
	return new ShrubberyCreationForm(target);
}
typedef AForm *(*formCreationFunction)(const std::string target);

AForm *Intern::makeForm(std::string formName, std::string target) {

	AForm *form = NULL;

	const std::string formNames[] = {
		"presidential pardon", 
		"robotomy request", 
		"shrubbery creation" 
	};

	formCreationFunction formCreation[3] = {
		createPresidentialPardonForm, 
		createRobotomyRequestForm, 
		createShrubberyCreationForm
	};

	for (int i = 0; i < 3; i++) {
		if (formName == formNames[i]) {
			std::cout << "Intern creates " << formName << " form" << std::endl;
			form = formCreation[i](target);
			break;
		}
	}
	if (form == NULL)
		std::cerr << "Intern cannot create " << formName << " form" << std::endl;
	return form;

}