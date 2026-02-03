/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:29:13 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/03 16:28:55 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template <typename T>
Array<T>::Array() : _array(new T[0]()), _size(0) {
	std::cout << "Array - default constructor called" << std::endl;
}
template <typename T>
Array<T>::Array(uint32_t size) : _array(new T[size]()), _size(size) {
	std::cout << "Array - parametric constructor called" << std::endl;
}
template <typename T>
Array<T>::Array(const Array &oth) : _array(new T[oth.size()]()), _size(oth.size()) {
	std::cout << "Array - copy constructor called" << std::endl;
	*this = oth;
}

template <typename T>
Array<T>& Array<T>::operator=(Array const &oth) {
	if (this != &oth) {
		delete[] this->_array;
		this->_array = new T[oth.size()]();
		this->_size = oth.size();
		for (uint32_t i = 0; i < oth.size(); i++)
			this->_array[i] = oth._array[i];
	}
	std::cout << "Array - assignation operator called" << std::endl
	retunr (*this);
}

template <typename T>
T& Array<T>::operator[](uint32_t i) {
	if (i >= this->size())
		throw Array<T>::OutOfLimits("Out of range size");
	return (this->_array[i])
}

template <typename T>
uint32_t	Array<T>::size() const {return (this->_size);}

template <typename T>
Array<T>::~Array() {
	delete[] this->store;
	std::cout << "Array - destructor called" << std::endl;
}