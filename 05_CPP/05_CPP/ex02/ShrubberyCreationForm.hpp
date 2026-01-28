/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:24:23 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/28 08:56:50 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>
#define EXEC_SCF 137
#define SIGN_SCF 145

class Bureaucrat;

class ShrubberyCreationForm : public AForm{
	private:
		std::string	_target;
		const	int	_signGrade;
		const	int	_execGrade;
		ShrubberyCreationForm();
	public:
		ShrubberyCreationForm(const std::string &target);
		ShrubberyCreationForm(const ShrubberyCreationForm &oth);
		ShrubberyCreationForm	operator=(const ShrubberyCreationForm &oth);
		~ShrubberyCreationForm();
		void	execute(Bureaucrat const & executor) const;
		void	checkValue(int value, bool isSigned) const;
		void	generateChristmasTree(int height, std::ofstream &outputFile) const;
		
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