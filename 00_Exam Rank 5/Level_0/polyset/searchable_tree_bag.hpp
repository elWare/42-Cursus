/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:23:40 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/21 10:22:35 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "extra_class/searchable_bag.hpp"
#include "extra_class/tree_bag.hpp"

class searchable_tree_bag : public searchable_bag, public tree_bag {
	public:
		searchable_tree_bag() : tree_bag() {}
		searchable_tree_bag(const searchable_tree_bag &t_array) : tree_bag(t_array) {}
		searchable_tree_bag	&operator=(const searchable_tree_bag &t_array) {
			if (this != &t_array)
				tree_bag::operator=(t_array);
			return (*this);
		}
		~searchable_tree_bag() {clear();}

		bool	has(int val) const {
			node *current = tree;
			while (current){
				if (current->value == val)
					return true;
				else if (current->value < val)
					current = current->l;
				else
					current = current->r;
			}
			return false;
		}

};