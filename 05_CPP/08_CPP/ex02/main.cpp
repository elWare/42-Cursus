/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:16:02 by jumarque          #+#    #+#             */
/*   Updated: 2026/03/11 20:38:51 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <list>
#include <iostream>

int main() {

	MutantStack<int> mstack;						// Create an instance of MutantStack

	mstack.push(5);									// Add the number 5 to the stack
	mstack.push(17);								// Add the number 17 to the stack

	std::cout << mstack.top() << std::endl;			// Print the top of the stack (17)
	mstack.pop();									// Remove the top of the stack (17)
	std::cout << mstack.size() << std::endl;		// Print the size of the stack with only 1 element (1)
	mstack.push(3);									// Add the number 3 to the stack
	mstack.push(5);									// Add the number 5 to the stack
	mstack.push(737);								// Add the number 737 to the stack
	//[...]
	mstack.push(0);									// Add the number 0 to the stack
	MutantStack<int>::iterator it = mstack.begin();	// Create an iterator for the beginning of the stack
	MutantStack<int>::iterator ite = mstack.end();	// Create an iterator for the end of the stack
	++it;											// Move the iterator to the next element
	--it;											// Move the iterator to the previous element
	while (it != ite)								// Loop through the stack while the iterator is not at the end
	{
		std::cout << *it << std::endl;				// Print the element at the iterator
		++it;										// Move the iterator to the next element
	}
	std::stack<int> s(mstack);						// Create a stack from the MutantStack to test the copy constructor
	
	return 0;
}

/* // My test function to test the MutantStack with a stack and a list

template <typename Container>
void testContainer(Container &container) {
	container.push("a");
	container.push("bebe");
	std::cout << "Top element: " << container.top() << std::endl;
	container.pop();
	std::cout << "Size: " << container.size() << std::endl;
	container.push("día");
	container.push("el");
	container.push("final");
	container.push("i");

	typename Container::iterator it = container.begin();
	typename Container::iterator ite = container.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
}

template <>
void testContainer(std::list<int> &container) {
	container.push_back(5);
	container.push_back(17);
	std::cout << "Top element: " << container.back() << std::endl;
	container.pop_back();
	std::cout << "Size: " << container.size() << std::endl;
	container.push_back(3);
	container.push_back(5);
	container.push_back(737);
	container.push_back(0);

	std::list<int>::iterator it = container.begin();
	std::list<int>::iterator ite = container.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
}

int	main() {
	cout << BLUE << "Testing MutantStack with stack" << RESET << endl;
	MutantStack<std::string> mstack;
	testContainer(mstack);

	cout << BLUE << "Testing MutantStack with list" << RESET << endl;
	std::list<int> list;
	testContainer(list);

	return 0;
} */
