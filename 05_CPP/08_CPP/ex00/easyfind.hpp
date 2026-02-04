/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:54:10 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/04 12:21:26 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <algorithm>
#include <exception>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

class EasyFindException : public std::out_of_range {
	public:
		EasyFindException(std::string message) : std::out_of_range(message) {}
};

#include "easyfind.tpp"

template <typename T>
bool	easyfind(T &container, int toFind);