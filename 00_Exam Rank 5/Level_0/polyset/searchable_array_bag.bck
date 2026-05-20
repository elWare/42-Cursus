/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:41:25 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/16 11:11:19 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "extra_class/searchable_bag.hpp"
#include "extra_class/array_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag {
	
	public:
		searchable_array_bag() : array_bag() {}
		searchable_array_bag(const searchable_array_bag &other) : array_bag(other) {}
		searchable_array_bag &operator=(const searchable_array_bag &other) {
			if (this != &other)
				array_bag::operator=(other);
			return *this;
		}
		~searchable_array_bag() {}
		bool	has(int item) const {
			for (int i = 0; i < size; i++)
				if (data[i] == item)
					return (true);
			return false;
		}
};