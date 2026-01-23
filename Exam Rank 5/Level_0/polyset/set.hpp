/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:05:52 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/21 13:20:46 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "extra_class/searchable_bag.hpp"

class set {
	private:
		searchable_bag &bag;
	public:
		set(searchable_bag &s_bag) : bag(s_bag) {}
		~set() {}

		void	insert(int val) const {
			if (!bag.has(val))
				bag.insert(val);
		}
		void	insert(int *items, int count) {
			for (int i = 0 ; i < count; i++)
				if (!bag.has(items[i]))
					bag.insert(items[i]);
		}
		bool	has(int val) const {return (bag.has(val));}
		void	print() {bag.print();}
		void	clear() {bag.clear();}
		searchable_bag	&get_bag() {return bag;}
};