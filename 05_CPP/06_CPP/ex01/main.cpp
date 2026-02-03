/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:53:05 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/03 13:18:42 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serialization.hpp"

using std::cerr; using std::cout; using std::endl; 

int	main() {

	Data	*ptr;
	Data	*ptrNew = NULL;

	ptr = new Data;
	ptr->str = "Up2u 🤗";

	cout << "\n";
	cout << GREEN << "* * * Executing Serialization * * *\n" << RESET << endl;

	cout << "    Original ptr string: " << ptr->str << endl;
	cout << "\n";

	cout << "     Original ptr : " << RED << ptr << RESET <<endl;
	uintptr_t converted = serialize(ptr);
	cout << "       Serielized : " << converted << endl;
	ptrNew = deserialize(converted);
	cout << "     Deserialized : " << RED << ptrNew << RESET << endl;
	cout << "\n";

	cout << "    And, new ptr string: " << ptrNew->str << endl;

	cout << "\n";
	cout << GREEN << "* * *  Ending  Serialization  * * *\n" << RESET << endl;

	delete ptr;

}