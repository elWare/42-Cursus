/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 08:33:05 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/28 08:58:08 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <ctime>
#include <cstdlib>
#define SIGN_RRF 72
#define EXEC_RRF 45


class Bureaucrat;

class RobotomyRequestForm : public AForm{
	private:
		std::string	_target;
		const	int	_signGrade;
		const	int	_execGrade;
		RobotomyRequestForm();
	public:
		RobotomyRequestForm(const std::string &target);
		RobotomyRequestForm(const RobotomyRequestForm &oth);
		RobotomyRequestForm	operator=(const RobotomyRequestForm &oth);
		~RobotomyRequestForm();
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