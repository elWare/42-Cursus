/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:55:33 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/08 20:19:49 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#define MICROSEC 1000000

#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define MAGENTA "\033[1;35m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

class PmergeMe {
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &oth);
		PmergeMe &operator=(const PmergeMe &oth);
		~PmergeMe();

		void sortList(int argc, char *argv[]);
		void sortVector(int argc, char *argv[]);
	
		class InvalidInput : public std::exception {
			public:
				virtual const char *what() const throw();
		};
};