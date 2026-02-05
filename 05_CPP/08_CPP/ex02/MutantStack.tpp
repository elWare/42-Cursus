/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:29:56 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/05 12:34:58 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

template <typename T>
MutantStack<T>::MutantStack() {
	std::cout << "MutantStack " << GREEN "constructor" << RESET " called" << std::endl;
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &oth) {
	*this = oth;
	std::cout << "MutantStack " << GREEN "copy constructor" << RESET " called" << std::endl;
}

template <typename T>
MutantStack<T>	&MutantStack<T>::operator=(const MutantStack &oth) {
	std::cout << "MutantStack " << GREEN "copy assignment operator" << RESET " called" << std::endl;
	std::stack<T>::operator=(oth);
	return (*this);
}

template <typename T> 
typename MutantStack<T>::iterator MutantStack<T>::begin() {
	return (this->c.begin());
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
	return (this->c.end());
}

template <typename T>
MutantStack<T>::~MutantStack() {
	std::cout << "MutantStack " << RED "destructor" << RESET " called" << std::endl;
}