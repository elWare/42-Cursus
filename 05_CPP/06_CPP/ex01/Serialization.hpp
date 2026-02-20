/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialization.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:23:31 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/19 13:51:43 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Data.hpp"

class Serialization {

	private:
		Serialization();
		Serialization(const Serialization &oth);
		Serialization	operator=(const Serialization &oth);
	public:
		~Serialization();
		static	uintptr_t	serialize(Data *ptr);
		static	Data		*deserialize(uintptr_t raw);
};