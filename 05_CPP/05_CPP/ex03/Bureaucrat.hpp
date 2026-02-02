/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:29:15 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/27 13:48:25 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <ostream>
#include <stdexcept>
#include "AForm.hpp"

#define	MAX_GRADE 1
#define	MIN_GRADE 150

class AForm;

class Bureaucrat {
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat();
		Bureaucrat(const std::string &n_name, int grade);
		Bureaucrat(const Bureaucrat &oth_buro);
		~Bureaucrat();
		Bureaucrat	operator=(const Bureaucrat &oth_buro);
		const std::string	getName() const;
		int		getGrade() const;
		void	incrementGrade();
		void	decrementGrade();
		void	checkValue(int grade);
		bool	getIsSigned(const AForm &aform) const;
		void	signForm(AForm &aform);
		void	executeForm(AForm &aform) const;

		class	GradeTooHighException : public std::out_of_range {
			public:
				GradeTooHighException(const char *message) : std::out_of_range(message) {}
		};
		class	GradeTooLowException : public std::out_of_range {
			public:
				GradeTooLowException(const char *message) : std::out_of_range(message) {}
		};
		class	ErrorSigned : public std::out_of_range {
			public:
				ErrorSigned(const char *message) : std::out_of_range(message) {}
		};
	friend std::ostream	&operator<<(std::ostream &os, const Bureaucrat &buro);
};
