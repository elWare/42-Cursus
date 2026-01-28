/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:20:16 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/26 12:03:09 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Bureaucrat.hpp"
#include <iostream>
#include <exception>

class Bureaucrat;

class AForm
{
private:
	const	std::string	_name;
	bool	_isSigned;
	int		_gradeToSign;
	int		_gradeToExec;
	
public:
	AForm();
	AForm(const AForm &oth);
	AForm(std::string name, int gradeToSign, int gradeToExec);
	void	operator=(const AForm &oth);
	~AForm();
	
	void	checkVaule(int grade);
	int		getGradeToSign() const;
	int		getGradeToExec() const;
	std::string getName() const;
	void	beSigned(Bureaucrat &buro);
	bool	getIsSigned() const;

	virtual void	execute(Bureaucrat const &executor) const = 0;

	class	GradeTooHighException : public std::out_of_range {
		public:
			GradeTooHighException(const char *message) : std::out_of_range(message) {}
	};
	class	GradeTooLowException : public std::out_of_range {
		public:
			GradeTooLowException(const char *message) : std::out_of_range(message) {}
	};
	friend std::ostream &operator<<(std::ostream &os, const AForm &aform);
};

