/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 20:20:22 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/09 13:16:57 by jumarque         ###   ########.fr       */
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

PmergeMe::~PmergeMe() {
	std::cout << BLUE "Destructor PM called" RESET << std::endl;
}

const char *PmergeMe::InvalidInput::what() const throw() {
	return RED "Invalid input" RESET;
}

// Utils
unsigned int	ft_stou(const std::string &str) {
	std::stringstream	ss(str);
	unsigned int		numb;

	ss >> numb;
	return (numb);
}

static void	printVector(const std::vector<unsigned int> &v) {
	std::vector<unsigned int>::const_iterator it;
	int i = 0;
	
	for (it = v.begin(); it != v.end(); it++) {
		if (i < 8) {
			std::cout << *it << " ";
			i++;
		}
		else {
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl;
}

static void	printList(const std::list<unsigned int> &l){
	std::list<unsigned int>::const_iterator	it;
	int	i = 0;
	
	for (it = l.begin(); it != l.end(); it++){
		if (i < 8) {
			std::cout << *it << " ";
			i++;
		}
		else {
			std::cout << "[...]";
			break;
		}
	}
	std::cout << std::endl;
}

// Vectors

static	std::vector<unsigned int>
joinVec(std::vector<unsigned int> &id, std::vector<unsigned int> &dd) {
	std::vector<unsigned int> res;

	while (!id.empty() && !dd.empty()) {
		if (id.front() <= dd.front()) {
			res.push_back(id.front());
			id.erase(id.begin());
		} else {
			res.push_back(dd.front());
			dd.erase(dd.begin());
		}
	}

	while (!id.empty()) {
		res.push_back(id.front());
		id.erase(id.begin());
	}
	while (!dd.empty()) {
		res.push_back(dd.front());
		dd.erase(dd.begin());
	}
	return res;
}

static	std::vector<unsigned int> insertVec(std::vector<unsigned int> &v) {
	if (v.size() <= 1)
		return v;
	int mid = v.size() / 2;
	std::vector<unsigned int>	id(v.begin(), v.begin() + mid);
	std::vector<unsigned int>	dd(v.begin() + mid, v.end());
	id = insertVec(id);
	dd = insertVec(dd);

	return (joinVec(id, dd));
}

void	PmergeMe::sortVector(int argc, char *argv[]) {
	std::vector<unsigned int> res;
	
	for (int i = 1; i < argc; i++)
		res.push_back(ft_stou(argv[i]));
	std::cout << "\n\tVECTOR - " << BLUE "Before sorting: " << RESET;
	printVector(res);

	std::clock_t	start = std::clock();
	res = insertVec(res);

	double duration = static_cast<double>(std::clock() 
	- start) / static_cast<double>CLOCKS_PER_SEC 
	* MICROSEC;
	
	std::cout  << "\tVECTOR - " << GREEN"After sorting : " << RESET;
	printVector(res);

	std::cout << "\nVector of " << BLUE << argc - 1 
	<< " elements " << RESET << "sorted in : " 
	<< GREEN << duration << " µs" << RESET << std::endl;
	
}

// LIST

static std::list<unsigned int> 
joinList(std::list<unsigned int> &id, 
std::list<unsigned int> &dd) {

	std::list<unsigned int> res;


	while (!id.empty() && !dd.empty()) {
		if (id.front() <= dd.front()) {
			res.push_back(id.front());
			id.erase(id.begin());
		} else {
			res.push_back(dd.front());
			dd.erase(dd.begin());
		}
	}
	
	while (!id.empty()) {
		res.push_back(id.front());
		id.erase(id.begin());
	}

	while (!dd.empty()) {
		res.push_back(dd.front());
		dd.erase(dd.begin());
	}
	return res;
}


static std::list<unsigned int> insertList(std::list<unsigned int> &l) {
	if (l.size() <= 1)
		return l;

	int mid = l.size() / 2;
	
	std::list<unsigned int> id;
	std::list<unsigned int> dd;
	
	for (int i = 0; i < mid; i++) {
		id.push_back(l.front());
		l.pop_front();
	}
	dd = l;

	id = insertList(id);
	dd = insertList(dd);
	
	return joinList(id, dd);
}

void PmergeMe::sortList(int argc, char *argv[]) {
	std::list<unsigned int> res;

	for (int i = 1; i < argc; i++) {
		res.push_back(ft_stou(argv[i]));
	}

	std::cout << "\tLIST - " << BLUE << "Before sorting :  " << RESET;
	printList(res);

	std::clock_t start = std::clock();
	res = insertList(res);
	
	double duration = static_cast<double>(std::clock() 
	- start) / static_cast<double>CLOCKS_PER_SEC 
	* MICROSEC;

	std::cout  << "\tLIST - " << GREEN << "After sorting  :  " << RESET;
	printList(res);
	std::cout << std::endl;

	std::cout << "List of " << BLUE << argc - 1 
	<< " elements " << RESET << "sorted in  :  " 
	<< GREEN << duration << " µs" << RESET << std::endl;
}