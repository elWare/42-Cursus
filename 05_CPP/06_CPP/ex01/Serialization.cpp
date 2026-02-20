/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialization.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:42:04 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/19 17:10:23 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serialization.hpp"

uintptr_t	Serialization::serialize(Data *ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data	*Serialization::deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data*>(raw));
}

Serialization::~Serialization(){
	std::cout << "Serialization finisher called" << std::endl;
}