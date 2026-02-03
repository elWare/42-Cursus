/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:11:16 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/03 13:20:04 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

int	main() {

	Base	*ptr;

	cout << "\n* * * Executing Test * * *\n" << endl;

	ptr = generate();

	cout << "\n";
	identify(ptr);
	identify(*ptr);

	delete ptr;

	cout << "\n* * *  Ending  Test  * * *\n" << endl;

	return 0;

}	