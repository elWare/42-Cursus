/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:04:48 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/21 10:20:19 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "extra_class/array_bag.hpp"
#include "extra_class/searchable_bag.hpp"

class searchable_array_bag : public searchable_bag, public array_bag {
	public:
		searchable_array_bag() : array_bag() {}
		searchable_array_bag(const searchable_array_bag &a_bag) : array_bag(a_bag) {}
		searchable_array_bag	operator=(const searchable_array_bag &a_bag) {
			if (this != &a_bag)
				array_bag::operator=(a_bag);
		}
		~searchable_array_bag() {clear();}

		bool	has(int val) const {
			for (int i = 0; i < size; i++)
				if(this->data[i] == val)
					return true;
			return (false);
		}
};