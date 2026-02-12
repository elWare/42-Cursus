/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:05:35 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/12 16:51:44 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"


void	Form::checkVaule(int grade) {
	if (grade < MAX_GRADE) 
		throw	Form::GradeTooHighException("Form grade out of max range");
	else if (grade > MIN_GRADE) 
		throw	Form::GradeTooLowException("Form grade out of min range");
}

Form::Form(const std::string name, int gradeToSign, int gradeToExec) : _name(name) {
	Form::checkVaule(gradeToSign);
	_gradeToSign = gradeToSign;
	Form::checkVaule(gradeToExec);
	_gradeToExec = gradeToExec;
	_isSigned = false;
	std::cout << "Default Form constructor called" << std::endl;
}

Form::Form(const Form &oth) : _name (oth._name) {
	_isSigned = oth._isSigned;
	_gradeToExec = oth._gradeToExec;
	_gradeToSign = oth._gradeToSign;
	std::cout << "Default Form Copy constructor called" << std::endl;
}

Form::~Form() {	std::cout << "Default Form destructor called" << std::endl; }

Form	Form::operator=(const Form &oth) {
	_isSigned = oth._isSigned;
	_gradeToExec = oth._gradeToExec;
	_gradeToSign = oth._gradeToSign;
	return (*this);
}

int		Form::getGradeToExec() const { return _gradeToExec;}
int		Form::getGradeToSign() const { return _gradeToSign;}
bool	Form::getIsSigned() const { return _isSigned;}
const std::string Form::getName() const { return _name;}

void	Form::beSigned(Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() >= this->getGradeToSign())
		throw	Form::GradeTooLowException("grade is too low to sign.");
	else
		std::cout << bureaucrat.getName() << " signed Form " << this->getName() << std::endl;
	this->_isSigned = true;
}

std::ostream &operator<<(std::ostream &os, const Form &form) {
	os << "Form " << form.getName() << " with grade to sign " << form.getGradeToSign() 
	<< " and grade to execute " << form.getGradeToExec() << " is ";
	if (form.getIsSigned())
		os << "signed";
	else
		os << "not signed";
	return os;
};