/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:05:35 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/25 13:42:19 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

bool Form::checkVaule(int grade) {
	if (grade < MAX_GRADE) {
		throw	GradeTooHighException("Form grade out of max range");
		return (false);
	}
	else if (grade > MIN_GRADE) {
		throw	GradeTooLowException("Form grade out of min range");
		return (false);
	}
	else
		return (true);
}

Form::Form(const std::string name, int gradeToSign, int gradeToExec) : _name(name) {
	try {
		if (this->checkVaule(gradeToSign))
			_gradeToSign = gradeToSign;
	}
	catch(const std::out_of_range& e) {
		_gradeToSign = 1;
		std::cerr << e.what() << '\n';
	}
	try {
		if (this->checkVaule(gradeToExec))
			_gradeToExec = gradeToExec;
	}
	catch (const std::out_of_range& e) {
		_gradeToExec = 1;
		std::cerr << e.what() << '\n';
	}
	_isSigned = false;
	std::cout << "Default Form constructor called" << std::endl;
}