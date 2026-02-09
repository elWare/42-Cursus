/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:46:09 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/09 12:47:33 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[]) {

	if (argc < 2) {										// if the number of arguments is less than 2
		std::cerr << PmergeMe::InvalidInput().what() << std::endl;	// print the exception message
		return EXIT_FAILURE;							// return 1
	}

	PmergeMe p;											// create a PmergeMe object

	try {
		for (int i = 1; i < argc; i++) {
			if (std::string(argv[i]).find_first_not_of("0123456789") != std::string::npos)
				throw PmergeMe::InvalidInput();			// throw the exception if the string contains a non-digit character
		}
		std::vector<unsigned int> tmp;					// create a vector object named tmp
		for (int i = 1; i < argc; i++) {
			tmp.push_back(ft_stou(argv[i]));			// convert the string to unsigned int and push it to the vector
		}
		std::vector<unsigned int>::iterator it1;		// create an iterator to browse the vector
		std::vector<unsigned int>::iterator it2;		// create an iterator to browse the vector
		for (it1 = tmp.begin(); it1 != tmp.end(); it1++) {
			for (it2 = it1 + 1; it2 != tmp.end(); it2++) {
				if (*it1 == *it2)
					throw PmergeMe::InvalidInput();		// throw the exception if the vector contains duplicate elements
			}
		}
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;						// print the exception message
		return EXIT_FAILURE;							// return 1
	}

	p.sortVector(argc, argv);							// sort the vector
	std::cout << std::endl;
	p.sortList(argc, argv);								// sort the list
	
	return EXIT_SUCCESS;								// return 0
}