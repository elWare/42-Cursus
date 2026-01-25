/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:45:23 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/25 13:46:34 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

using std::cerr;
using std::cout;
using std::endl;

int main() {

	cout << "\n* * * 📜 Welcome to the Bureaucrat and Form test 📜 * * *" << endl;

	cout << "\n    * * * * * * *  🧪 General test  🧪  * * * * * * *    \n" << endl;{

		Form	a("Form", 66, 66);		// Create a form with grade to sign and execute 66
		Form	b(a);					// Copy the form a
		Form	c = b;					// Copy the form b

		cout << "Form a: " << a.getName() << "🖊️ grade to sign: " << a.getGradeToSign() << " 🧑‍⚖️ grade to execute: " << a.getGradeToExec() << endl;
		cout << "Form b: " << b.getName() << "🖊️ grade to sign: " << b.getGradeToSign() << " 🧑‍⚖️ grade to execute: " << b.getGradeToExec() << endl;
		cout << "Form c: " << c.getName() << "🖊️ grade to sign: " << c.getGradeToSign() << " 🧑‍⚖️ grade to execute: " << c.getGradeToExec() << endl << "\n";

	}

	cout << "\n* * * * * * *  📉  Grade low and high  📈   * * * * * * *\n" << endl;{

		try {
			Form a(" A ", MIN_GRADE - 1, MIN_GRADE - 1);	// Value of grade is too low now
		} catch (std::exception &e) {
			cerr << e.what() << endl;					// Print the exception
		}

		try {
			Form b(" B ", MAX_GRADE + 1, MAX_GRADE + 1);	// Value of grade is too high now
			cout << b.getName() << "🖊️ grade to sign: " << b.getGradeToSign() << " 🧑‍⚖️ grade to execute: " << b.getGradeToExec() << endl;
		} catch (std::exception &e) {
			cerr << e.what() << endl;					// Print the exception
		}

	}

	cout << "\n* * * * * * *  📝 Able to sign all forms 📝 * * * * * * *\n" << endl;{

		try {

			Bureaucrat a1("Donald ", MAX_GRADE);				// Create a bureaucrat with the maximum grade
			cout << a1 << endl;

			Form f1("Form 1 ", MAX_GRADE, 20);				// Create a form with grade to sign and execute 20
			cout << f1.getName() << " 🖊️  grade to sign: " << f1.getGradeToSign() << " 🧑‍⚖️ grade to execute: " << f1.getGradeToExec() << endl;

			Form f2("Form 2 ", 66, MIN_GRADE);				// Create a form with grade to sign 66 and
			cout << f2.getName() << " 🖊️  grade to sign: " << f2.getGradeToSign() << " 🧑‍⚖️ grade to execute: " << f2.getGradeToExec() << endl;

			f1.beSigned(a1);								// Sign the form 1
			cout << f1 << endl;								// Print the form 1
			f2.beSigned(a1);								// Sign the form 2
			cout << f2 << endl;								// Print the form 2
		} catch (std::exception &e) {
			cerr << e.what() << endl;						// Print the exception
		}
	}

	cout << "\n* * * * * *  🚫 Unable to sign all forms 🚫   * * * * * *\n" << endl;{

		try {

			Bureaucrat a2("Joe ", MIN_GRADE);				// Create a bureaucrat with the maximum grade
			cout << a2 << endl;

			Form f3("Form 3 ", MIN_GRADE, 20);				// Create a form with grade to sign and execute 20
			cout << f3.getName() << " 🖊️  grade to sign: " << f3.getGradeToSign() << " 🧑‍⚖️ grade to execute: " << f3.getGradeToExec() << endl;

			Form f4("Form 4 ", 66, MAX_GRADE);				// Create a form with grade to execute 66
			cout << f4.getName() << " 🖊️  grade to sign: " << f4.getGradeToSign() << " 🧑‍⚖️ grade to execute: " << f4.getGradeToExec() << endl;

			f3.beSigned(a2);								// Sign the form 3
			cout << f3 << endl;								// Print the form 3
			f4.beSigned(a2);								// Sign the form 4
			cout << f4 << endl;								// Print the form 4
		} catch (std::exception &e) {
			cerr << e.what() << endl;						// Print the exception
		}
	}

	return 0;

}