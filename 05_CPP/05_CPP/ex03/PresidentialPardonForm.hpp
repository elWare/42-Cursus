/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:38:57 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/28 08:50:25 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#define SIGN 25
#define EXEC 5


class Bureaucrat;

class PresidentialPardonForm : public AForm{
	private:
		std::string	_target;
		const	int	_signGrade;
		const	int	_execGrade;
		PresidentialPardonForm();
	public:
		PresidentialPardonForm(const std::string &target);
		PresidentialPardonForm(const PresidentialPardonForm &oth);
		PresidentialPardonForm	operator=(const PresidentialPardonForm &oth);
		~PresidentialPardonForm();
		void	execute(Bureaucrat const & executor) const;
		void	checkValue(int value, bool isSigned) const;
		
		int	getExecGrade() const;
		int	getSignGrade() const;

		class	ErrorValueExecute : public std::out_of_range {
			public:
				ErrorValueExecute(const char *message) : std::out_of_range(message) {}
		};
		class	ErrorSigned : public std::out_of_range {
			public:
				ErrorSigned(const char *message) : std::out_of_range(message) {}
		};
};