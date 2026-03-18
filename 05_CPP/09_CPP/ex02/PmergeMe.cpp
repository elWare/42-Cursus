/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 20:20:22 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/17 12:36:50 by jumarque         ###   ########.fr       */
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

	char	*endptr = NULL;
	long result = std::strtol(str.c_str(), &endptr, 0);

	if (result > static_cast<long>(-1U)) {
		throw std::out_of_range(RED "number out of range" RESET);
	}

	return (static_cast<unsigned int>(result));
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

void	PmergeMe::duplicateValue(std::vector<unsigned int> &o_v){
	std::vector<unsigned int> v(o_v);
	
	if (v.size() < 2) return ;
	
	std::sort(v.begin(), v.end());

	if (std::adjacent_find(v.begin(), v.end()) != v.end())
		throw std::out_of_range(RED "numbers duplicated" RESET);
}


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

void	PmergeMe::sortVector(std::vector<unsigned int>& res) {

	std::cout << "\n\tVECTOR - " << BLUE "Before sorting: " << RESET;
	printVector(res);

	std::clock_t	start = std::clock();
	res = insertVec(res);

	double duration = static_cast<double>(std::clock() 
	- start) / static_cast<double>CLOCKS_PER_SEC 
	* MICROSEC;
	
	std::cout  << "\tVECTOR - " << GREEN"After sorting : " << RESET;
	printVector(res);

	std::cout << "\nVector of " << BLUE << res.size() 
	<< " elements " << RESET << "sorted in : " 
	<< GREEN << duration << " µs" << RESET << std::endl;
	
}

// LIST

static std::list<unsigned int> joinList(std::list<unsigned int> &id, std::list<unsigned int> &dd) {

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

void PmergeMe::sortList(std::list<unsigned int> &res) {

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

	std::cout << "List of " << BLUE << res.size()
	<< " elements " << RESET << "sorted in  :  " 
	<< GREEN << duration << " µs" << RESET << std::endl;
}