/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:09:27 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/04 12:22:42 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

template <typename T>
bool	easyfind(T &container, int toFind) {
	if (std::find(container.begin(), container.end(), toFind) == container.end())
		throw EasyFindException("Error: Value not found in container 😡");
	return (true);
}