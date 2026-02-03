/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:27:46 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/03 13:13:24 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Base {
	public:
		virtual ~Base();
};

Base	*generate();
void	identify(Base* p);
void	identify(Base& p);