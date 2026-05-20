/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:13:15 by jumarque          #+#    #+#             */
/*   Updated: 2025/12/19 13:54:21 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class vect2 {
	private:
		int	x;
		int	y;
		
	public:
		vect2(): x(0), y(0) {}
		vect2(int n_x, int n_y) : x(n_x), y(n_y) {}
		vect2(const vect2 &other): x(other.x), y(other.y) {}
		~vect2() {}
		vect2	&operator=(const vect2 &other) {
			if (this != &other)
			{
				x = other.x;
				y = other.y;
			}
			return (*this);
		}
		
		// Composición de vectores
		int	&operator[](int i)
		{
			if (i == 0)
				return x;
			else
				return y;
		}
		
		int operator[](int i) const 
		{
			if (i == 0)
				return x;
			else
				return y;
		}

		// Operadores de suma e incremento
		
		vect2 operator+(const vect2 &oth) const {
			 return vect2(x + oth.x, y + oth.y);
		}
		vect2 &operator+= (const vect2 oth) {
			x += oth.x;
			y += oth.y;
			return (*this);
		}
		vect2 &operator++() {
			x ++;
			y ++;
			return (*this);
		}
		vect2 operator++(int) {
			vect2 tmp(*this);
			x++;
			y++;
			return (tmp);
		}
		vect2 operator-(const vect2 &oth) const {
			return vect2(x - oth.x, y - oth.y);
		}
		vect2 &operator-=(const vect2 &oth) {
			x -= oth.x;
			y -= oth.y;
			return (*this);
		}
		vect2 &operator--() {
			x--;
			y--;
			return (*this);
		}
		vect2 operator--(int) {
			vect2 tmp = *this;
			x--;
			y--;
			return (tmp);
		}
		vect2 operator-() const {
			return vect2(-x, -y);
		}

		vect2 operator*(int s) const {
			return vect2(x *s, y *s);
		}
		friend vect2 operator*(int s, const vect2 &v) {
			return vect2(v.x * s, v.y *s);
		}
		vect2 &operator*=(int s) { x *= s; y *= s; return *this; }

		bool	operator==(const vect2 &oth) const {
			return ((x == oth.x) && (y == oth.y));
		}

		bool	operator!=(const vect2 &oth) const {
			return (!(*this == oth));
		}

		friend	std::ostream &operator<<(std::ostream &os, const vect2 &v) {
			os << "{" << v[0] << "," << v[1] << "}";
			return os;
		}
};
