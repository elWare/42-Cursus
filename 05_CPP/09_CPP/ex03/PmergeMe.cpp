/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 20:20:22 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/08 20:24:06 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
	std::cout << BLUE "Default constructor called" RESET << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &oth) {
	*this = oth;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &oth) {
	(void)oth;
	return (*this);
}