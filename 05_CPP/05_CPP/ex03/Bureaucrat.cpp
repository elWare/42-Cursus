/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:13:33 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/12 16:56:12 by jumarque         ###   ########.fr       */
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
	std::cout << "Default Bureaucrat constructor call: " << _name <<std::endl;
};
Bureaucrat::Bureaucrat(const Bureaucrat &oth_buro) : _name(oth_buro._name) , _grade(oth_buro._grade) {
	std::cout << "Copy Bureaucrat constructor call: " << getName() << std::endl;
}
Bureaucrat::Bureaucrat(const std::string &name, int grade) : _name(name) {
	checkValue(grade);
	_grade = grade;
	std::cout << "Named Bureaucrat constructor call: " << name <<std::endl;
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
		checkValue(_grade - 1);
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
		checkValue(_grade + 1);
			_grade++;
	}
	catch(const std::out_of_range& e)
	{
		std::cerr << e.what() << '\n';
	}
}
void	Bureaucrat::signForm(AForm &form) {
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

bool Bureaucrat::getIsSigned(const AForm &oth) const {
	return (oth.getIsSigned());
}

void	Bureaucrat::executeForm(AForm &aform) const {
	try
	{
		aform.execute(*this);
		std::cout << aform.getName() << " executed by " << getName() <<std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
}
