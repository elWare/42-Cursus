/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:41:35 by sternero          #+#    #+#             */
/*   Updated: 2026/02/12 16:45:25 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

using std::cout;
using std::endl;
using std::cerr;

int main() {

	cout << "\n* * * * * * *  General Data  * * * * * * *\n" << endl; {

		Bureaucrat	a("Alice", 91);
		Bureaucrat	b(a);
		Bureaucrat	c = b;

		cout << endl;

		cout << "a: " << a;
		cout << "b: " << b;
		cout << "c: " << c;

		cout << endl;
	}

	cout << "\n* * * * * * Grade low and high * * * * * *\n" << endl; {
		try
		{
			Bureaucrat a("A", MIN_GRADE + 1);
			Bureaucrat b("B", MAX_GRADE - 1);
			cout << b;
			cout << a;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

	}

	cout << "* * *  Bad Increment and Decrement   * * *\n" << endl; {

		try {
			Bureaucrat c("Chief", MAX_GRADE);
			cout << "Trying to increment the grade of " << c.getName() << endl;
			c.incrementGrade();
			cout << c;
		} catch (std::exception &e) {
			cerr << e.what() << endl;
		}

		try {
			Bureaucrat d("Dodo", MIN_GRADE);
			cout << "Trying to decrement the grade of " << d.getName() << endl;
			d.decrementGrade();
			cout << d;
		} catch (std::exception &e) {
			cerr << e.what() << endl;
		}
	
	}

	cout << "* * * Possible operation with grade  * * *\n\n"; {

		try {
			Bureaucrat Donald("Donald", 9);
			Donald.incrementGrade();
			cout << "After increment 📈 ... " << Donald;
		} catch (std::exception &e) {
			cerr << e.what() << endl;
		}

		cout << endl;

		try {
			Bureaucrat Joe("Joe", 149);
			Joe.decrementGrade();
			cout << "After decrement 📉 ... " << Joe;
		} catch (std::exception &e) {
			cerr << e.what() << endl;
		}
	
	}

	cout << "\n* * * * * * End of the program * * * * * *\n";

	return 0;

}