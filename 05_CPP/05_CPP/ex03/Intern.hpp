/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42Malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:21:30 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/01 13:21:37 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include <string>

class Intern {

	public:

		Intern();
		Intern(const Intern &src);
		~Intern();

		Intern &operator=(const Intern &rhs);

		AForm *makeForm(std::string formName, std::string target);

};