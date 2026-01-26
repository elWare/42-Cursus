/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:05:35 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/26 10:06:21 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"


bool Form::checkVaule(int grade) {
	if (grade < MAX_GRADE) {
		throw	Form::GradeTooHighException("Form grade out of max range");
		return (false);
	}
	else if (grade > MIN_GRADE) {
		throw	Form::GradeTooLowException("Form grade out of min range");
		return (false);
	}
	else
		return (true);
}

Form::Form(const std::string name, int gradeToSign, int gradeToExec) : _name(name) {
	try {
		if (this->checkVaule(gradeToSign))
			_gradeToSign = gradeToSign;
		else
			_gradeToSign = 1;
	}
	catch(const std::out_of_range& e) {
		std::cerr << e.what() << '\n';
	}
	try {
		if (this->checkVaule(gradeToExec))
			_gradeToExec = gradeToExec;
		else
			_gradeToExec = 1;
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what() << '\n';
	}
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