/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:24:42 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/03 10:53:50 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <iostream>
#include <stdint.h>
#include <string>


#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

typedef struct Sdata {
	std::string str;
} Data;

uintptr_t	serialize(Data *ptr);
Data	*deserialize(uintptr_t	raw);