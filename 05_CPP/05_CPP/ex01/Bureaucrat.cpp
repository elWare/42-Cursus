/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:13:33 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/26 09:59:10 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

bool Bureaucrat::checkValue(int grade) {
	if (grade < MAX_GRADE) {
		throw	Bureaucrat::GradeTooHighException("Out of max range");
		return (false);
	}
	else if (grade > MIN_GRADE) {
		throw	Bureaucrat::GradeTooLowException("Out of min range");
		return (false);
	}
	else
		return (true);
}

Bureaucrat::Bureaucrat() : _name("Default_name"), _grade(MIN_GRADE) {
	std::cout << "Default constructor called" << std::endl;
};
Bureaucrat::Bureaucrat(const Bureaucrat &oth_buro) : _name(oth_buro._name) , _grade(oth_buro._grade) {
	std::cout << "Copy constructor called" << std::endl;
}
Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name) {
	try
	{
		if (checkValue(grade))
			_grade = grade;
		else
			_grade = MIN_GRADE;
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << e.what() << '\n';
	}
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
	try
	{
		if (checkValue(_grade - 1))
			_grade--;
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << e.what() << '\n';
	}
}
void	Bureaucrat::decrementGrade() {
	try
	{
		if (checkValue(_grade + 1))
			_grade++;
			
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << e.what() << '\n';
	}
}

void	Bureaucrat::signForm(Form &form) {
	try
	{
		form.beSigned(*this);
		std::cout << Bureaucrat::getName() << " signed " << form.getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << Bureaucrat::getName() << " couldn't sig " << form.getName() << " because " << e.what() << std::endl;
	}
}
