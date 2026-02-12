/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:05:35 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/26 12:03:00 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"


void	AForm::checkVaule(int grade) {
	if (grade < MAX_GRADE) 
		throw	AForm::GradeTooHighException("AForm grade out of max range");
	else if (grade > MIN_GRADE) 
		throw	AForm::GradeTooLowException("AForm grade out of min range");
}

AForm::AForm() : _name ("AForm_Default"), _gradeToSign(50), _gradeToExec(50) {
	std::cout << "Default AForm constructor called: " << getName() <<std::endl;
}

AForm::AForm(std::string name, int gradeToSign, int gradeToExec) :_name(name) {
	AForm::checkVaule(gradeToSign);
	_gradeToSign = gradeToSign;
	AForm::checkVaule(gradeToExec);
	_gradeToExec = gradeToExec;
	std::cout << "Parametric constructor called: " << name <<std::endl;
	_isSigned = false;
}

AForm::AForm(const AForm &oth) : _name (oth._name) {
	_isSigned = oth._isSigned;
	_gradeToExec = oth._gradeToExec;
	_gradeToSign = oth._gradeToSign;
	std::cout << "Default AForm Copy constructor called" << std::endl;
}

AForm::~AForm() {	std::cout << "Default AForm destructor called" << std::endl; }

void	AForm::operator=(const AForm &oth) {
	_isSigned = oth._isSigned;
	_gradeToExec = oth._gradeToExec;
	_gradeToSign = oth._gradeToSign;
}

int		AForm::getGradeToExec() const { return _gradeToExec;}
int		AForm::getGradeToSign() const { return _gradeToSign;}
bool	AForm::getIsSigned() const { return _isSigned;}
std::string AForm::getName() const { return _name;}

void	AForm::beSigned(Bureaucrat &bureaucrat) {
	if (bureaucrat.getGrade() >= this->getGradeToSign())
		throw	AForm::GradeTooLowException("grade is too low to sign.");
	else
		std::cout << bureaucrat.getName() << " signed " << this->getName() << std::endl;
	this->_isSigned = true;
}

std::ostream &operator<<(std::ostream &os, const AForm &aform) {
	os << "Form " << aform.getName() << " with grade to sign " << aform.getGradeToSign() 
	<< " and grade to execute " << aform.getGradeToExec() << " is ";
	if (aform.getIsSigned())
		os << "signed";
	else
		os << "not signed";
	return os;
};