/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 12:17:38 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/16 12:21:14 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "extra_class/searchable_bag.hpp"

class set {
	private:
		searchable_bag &bag;

	public:
		set(searchable_bag &bg) : bag(bg) {}
		~set() {};

		void insert(int item) {
			if (!bag.has(item))
				bag.insert(item);
		}
		void insert(int *items, int count) {
			for (int i = 0; i < count; i++)
				insert(items[i]);
		}
		bool has(int item) const { return bag.has(item);}
		void print() {bag.print();}
		void clear() {bag.clear();}
		searchable_bag &get_bag() { return bag;}
};