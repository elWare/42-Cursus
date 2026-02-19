/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:56:05 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/19 16:51:41 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>
# include <cstdlib>

class	Fixed
{
	private:
		int					_value;
		static const int	_fractBits = 8;
	public:
		Fixed(void);
		Fixed(const Fixed& other);
		Fixed(const float val);
		Fixed(const int val);
		~Fixed(void);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
		Fixed   &operator = (Fixed const &other); 

		// Operadores comparativos

		bool	operator > (Fixed const &other) const;
		bool	operator < (Fixed const &other) const;
		bool	operator >= (Fixed const &other) const;
		bool	operator <= (Fixed const &other) const;
		bool	operator == (Fixed const &other) const;
		bool	operator != (Fixed const &other) const;

		// Operadores Incrementales/Decrementales Pre y post
		Fixed	operator ++ (void);
		Fixed	operator ++ (int);
		Fixed	operator -- (void);
		Fixed	operator -- (int);

		// --- Sobrecarga de Operadores Aritméticos
		Fixed	operator + (Fixed const &other) const;
		Fixed	operator - (Fixed const &other) const;
		Fixed	operator * (Fixed const &other) const;
		Fixed	operator / (Fixed const &other) const;

		// --- Funciones Miembro Estáticas (min y max)
		static Fixed&	min(Fixed &a, Fixed &b);
		static const Fixed&	min(const Fixed &a, const Fixed &b);
		static Fixed&	max(Fixed &a, Fixed &b);
		static const Fixed&	max(const Fixed &a, const Fixed &b);

		static const Fixed&	test(int a, int b);
};

std::ostream &operator<<(std::ostream &stream, const Fixed &nbr);

#endif