/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:10:44 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/21 19:01:42 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <ostream>

class vect2 {
	private:
		int x;
		int y;
	public:
		vect2() : x(0), y(0) {}
		vect2(const vect2 &n_v) : x(n_v.x), y(n_v.y) {}
		vect2(int n_x, int n_y) : x(n_x), y(n_y) {}
		vect2	operator=(const vect2 &n_v) {
			if (this != &n_v){
				x = n_v.x;
				y = n_v.y;
			}
			return *this;
		}
		friend	std::ostream &operator<<(std::ostream &os, const vect2 &vec) {
			os << "{" << vec[0] << "," << vec[1] << "}";
			return os;
		}
		int	operator[](unsigned int index) const {
			if (index == 0)
				return x;
			else
				return y;
		}
		int	&operator[](unsigned int index) {
			if (index == 0)
				return x;
			else
				return y;
		}
		vect2	operator++() {
			x++;
			y++;
			return *this;
		}
		vect2	operator++(int) {
			vect2	tmp = *this;
			x++;
			y++;
			return (tmp);
		}
		vect2	operator--() {
			x--;
			y--;
			return (*this);
		}
		vect2	operator--(int) {
			vect2	tmp = *this;
			x--;
			y--;
			return (tmp);
		}
		vect2	operator+(const vect2 &oth) const {
			return vect2(x + oth.x, y + oth.y);
		}
		vect2	operator-(const vect2 &oth) const {
			return vect2(x - oth.x, y - oth.y);
		}
		vect2	operator-() {
			x = -x;
			y = -y;
			return (*this);
		}
		vect2	&operator+=(const vect2 &oth) {
			x = x + oth.x;
			y = y + oth.y;
			return (*this);
		}
		vect2	&operator-=(const vect2 &oth) {
			x = x - oth.x;
			y = y - oth.y;
			return (*this);
		}

		vect2	operator*(int s) const {
			return vect2(x * s, y * s);
		}
		friend	vect2	operator*(int s, const vect2 &vec) {
			return vect2(vec.x * s, vec.y *s);
		}
		vect2	operator*=(int s) {
			*this = *this * s;
			return (*this);
		}

		bool	operator==(const vect2 &oth) {
			return ((x == oth.x) && (y == oth.y));
		}
		bool	operator!=(const vect2 &oth) {
			return !(this == &oth);
		}
};