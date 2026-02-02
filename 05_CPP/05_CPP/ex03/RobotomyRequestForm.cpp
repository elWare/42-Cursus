/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:31:17 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/28 08:36:12 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string &target) : AForm("RRForm", SIGN_RRF, EXEC_RRF), _target("RRForm"),
						_signGrade(SIGN_RRF), _execGrade(EXEC_RRF) {
							std::cout << getName() << "Robotomy Form created by " << target << std::endl;
						}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &oth) : AForm(oth), _target(oth._target),
						_signGrade(SIGN_RRF), _execGrade(EXEC_RRF) {
							std::cout << getName() << "Robotomy Form created." << std::endl;
						}
RobotomyRequestForm::~RobotomyRequestForm() {}
RobotomyRequestForm RobotomyRequestForm::operator=(const RobotomyRequestForm &oth) {
	_target = oth._target;
	return (*this);
}


void	RobotomyRequestForm::checkValue(int grade, bool isSigned) const {
	if (grade > getExecGrade() || grade > getSignGrade())
		throw ErrorValueExecute("Can't execute AForm, incorrect grades.");
	else if (!isSigned)
		throw ErrorSigned("Form no signed");
}



void	RobotomyRequestForm::execute(Bureaucrat const & executor) const {
	std::cout << "Trying to exec "<< getName()<< std::endl;
	try
	{
		RobotomyRequestForm::checkValue(executor.getGrade(), this->getIsSigned());
		std::srand(time(NULL));
		std::cout <<"\n* * * * * * * drilling noises * * * * * * *\n" << std::endl;
		if (random() % 2 == 0)
			std::cout << this->getName() << " has been robotomized successfully" << std::endl;
		else
			std::cout << this->getName() << " has not been robotomized successfully" << std::endl;
	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

int RobotomyRequestForm::getExecGrade() const {return (_execGrade);}
int RobotomyRequestForm::getSignGrade() const {return (_signGrade);}
