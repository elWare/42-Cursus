/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:13:33 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/12 17:13:00 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

void Bureaucrat::checkValue(int grade) {
	if (grade < MAX_GRADE) 
		throw	GradeTooHighException("Out of max range");
	else if (grade > MIN_GRADE) 
		throw	GradeTooLowException("Out of min range");
}

Bureaucrat::Bureaucrat() : _name("Default_name"), _grade(MIN_GRADE) {
	std::cout << "Default constructor call" << std::endl;
};
Bureaucrat::Bureaucrat(const Bureaucrat &oth_buro) : _name(oth_buro._name) , _grade(oth_buro._grade) {
	std::cout << "Copy constructor call" << std::endl;
}
Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name) {
	checkValue(grade);
	_grade = grade;
	std::cout << "Named constructor call" << std::endl;
}
Bureaucrat::~Bureaucrat() {
	std::cout << "Destructor call" << std::endl;
}

Bureaucrat	Bureaucrat::operator=(const Bureaucrat &oth_bu) {
	_grade = oth_bu._grade;
	return (*this);
}
std::ostream	&operator<<(std::ostream &os, const Bureaucrat &buro) {
	os << buro.getName() << ", bureaucrat grade " << buro.getGrade() << std::endl;
	return (os);
}

const std::string	Bureaucrat::getName() const {
	return (_name);
}
int	Bureaucrat::getGrade() const {
	return (_grade);
}

void	Bureaucrat::incrementGrade() {
		checkValue(_grade - 1);
			_grade--;
}
void	Bureaucrat::decrementGrade() {
		checkValue(_grade + 1);
			_grade++;
}
