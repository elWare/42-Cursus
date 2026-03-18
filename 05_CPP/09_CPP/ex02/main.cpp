/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:46:09 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/17 12:34:10 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[]) {

	if (argc < 2) {
		std::cerr << PmergeMe::InvalidInput().what() << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<unsigned int> tmp_vect;
	std::list<unsigned int> tmp_list;

	try {
		for (int i = 1; i < argc; i++) {
			if (std::string(argv[i]).find_first_not_of("0123456789") != std::string::npos)
				throw PmergeMe::InvalidInput();
		}
		for (int i = 1; i < argc; i++) {
			unsigned val = ft_stou(argv[i]);
			tmp_vect.push_back(val);
			tmp_list.push_back(val);
		}
		PmergeMe::duplicateValue(tmp_vect);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	PmergeMe::sortVector(tmp_vect);
	std::cout << std::endl;
	PmergeMe::sortList(tmp_list);
	
	return EXIT_SUCCESS;
}