/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:40:20 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/28 09:44:09 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) : AForm("PPForm", SIGN, EXEC),
							_target(target), _signGrade(SIGN), _execGrade(EXEC) {
								std::cout << getName() << "Presidential Perdon Form created by " << target << std::endl;
							}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &oth) : AForm(oth),
							_target(oth._target), _signGrade(SIGN), _execGrade(EXEC) {
								std::cout << getName() << "Presidential Perdon Form created." << std::endl;
							}
PresidentialPardonForm::~PresidentialPardonForm() {}
PresidentialPardonForm PresidentialPardonForm::operator=(const PresidentialPardonForm &oth) {
	_target = oth._target;
	return (*this);
}


void	PresidentialPardonForm::checkValue(int grade, bool isSigned) const {
	if (grade > getExecGrade() || grade > getSignGrade())
		throw ErrorValueExecute("Can't execute Presidential AForm, incorrect grades.");
	else if (!isSigned)
		throw ErrorSigned("Form no signed");
}



void	PresidentialPardonForm::execute(Bureaucrat const & executor) const {
	try
	{
		PresidentialPardonForm::checkValue(executor.getGrade(), this->getIsSigned());
		std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

int PresidentialPardonForm::getExecGrade() const {return (_execGrade);}
int PresidentialPardonForm::getSignGrade() const {return (_signGrade);}
