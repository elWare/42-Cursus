/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 12:36:13 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/28 09:43:19 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("SCForm", SIGN_SCF, EXEC_SCF),
						_target("SCForm"), _signGrade(SIGN_SCF), _execGrade(EXEC_SCF) {
							std::cout << "Shrubbery form created by" << target << std::endl;
						}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &oth) : AForm(oth),
						_target(oth._target), _signGrade(SIGN_SCF), _execGrade(EXEC_SCF) {
							std::cout << getName() << "Shrubbery form created." << std::endl;
						}
ShrubberyCreationForm::~ShrubberyCreationForm() {}
ShrubberyCreationForm ShrubberyCreationForm::operator=(const ShrubberyCreationForm &oth) {
	_target = oth._target;
	return (*this);
}


void	ShrubberyCreationForm::checkValue(int grade, bool isSigned) const {
	if (grade > getExecGrade() || grade > getSignGrade())
		throw ErrorValueExecute("Can't execute Shrubbery Form, incorrect grades.");
	else if (!isSigned)
		throw ErrorSigned("Form no signed");
}



void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
	try
	{
		ShrubberyCreationForm::checkValue(executor.getGrade(), this->getIsSigned());
		std::cout << getName() << " has been executate by: " << std::endl;
		std::ofstream	outFile(_target + "_shrubbery");
		generateChristmasTree(10, outFile);
		outFile.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

int ShrubberyCreationForm::getExecGrade() const {return (_execGrade);}
int ShrubberyCreationForm::getSignGrade() const {return (_signGrade);}

void ShrubberyCreationForm::generateChristmasTree(int height, std::ofstream &outputFile) const {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < height - i - 1; ++j) {
			outputFile << " ";
		}
		for (int k = 0; k <= 2 * i; ++k) {
			outputFile << "*";
		}
		outputFile << "\n";
	}
	for (int j = 0; j < height - 1; ++j) {
		outputFile << " ";
	}
	outputFile << "*\n";
}