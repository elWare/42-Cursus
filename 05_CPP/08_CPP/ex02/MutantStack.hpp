/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 11:37:36 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/05 11:46:23 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <iostream>
#include <list>
#include <stack>

# define BLUE "\033[34m"
# define GREEN "\033[32m"
# define RED "\033[31m"
# define RESET "\033[0m"

template <typename T>
class MutantStack : public std::stack<T> {
	public:
		typedef typename std::stack<T>::container_type::iterator iterator;
		MutantStack();
		MutantStack(const MutantStack &oth);
		MutantStack	&operator=(const MutantStack &oth);
		~MutantStack();

		iterator	begin();
		iterator	end();
};

#include "MutantStack.tpp"