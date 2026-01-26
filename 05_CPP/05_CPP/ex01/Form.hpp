/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:20:16 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/26 10:02:31 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Bureaucrat.hpp"
#include <iostream>
#include <exception>

class Bureaucrat;

class Form
{
private:
	const	std::string	_name;
	bool	_isSigned;
	int		_gradeToSign;
	int		_gradeToExec;
	Form();
	
public:
	Form(const Form &oth);
	Form(const std::string name, int gradeToSign, int gradeToExec);
	Form	operator=(const Form &oth);
	~Form();
	
	// Aux
	bool	checkVaule(int grade);

	// Getter
	
	int		getGradeToSign() const;
	int		getGradeToExec() const;
	bool	getIsSigned() const;
	const std::string getName() const;

	void	beSigned(Bureaucrat &buro);

	// Exceptions

	class	GradeTooHighException : public std::out_of_range {
		public:
			GradeTooHighException(const char *message) : std::out_of_range(message) {}
	};
	class	GradeTooLowException : public std::out_of_range {
		public:
			GradeTooLowException(const char *message) : std::out_of_range(message) {}
	};
	friend std::ostream &operator<<(std::ostream &os, const Form &form);
};

