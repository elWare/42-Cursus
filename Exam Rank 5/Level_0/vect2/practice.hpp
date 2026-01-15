/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:41:19 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/12 11:32:54 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>
#include <sstream>
#include <ostream>

class vect2 {
	private:
		int	x;
		int	y;
	public:
		vect2() : x(0), y(0) {}
		vect2(const int &n_x, const int &n_y) : x(n_x), y(n_y) {}
		vect2(const vect2 &oth_v) : x(oth_v.x), y(oth_v.y) {}
		vect2	operator=(const vect2 &oth_v) {
			x = oth_v.x;
			y = oth_v.y;
			return (*this);
		}
		~vect2() {};

	friend	std::ostream &operator<<(std::ostream &os, const vect2 &vect) {
		os << "{" << vect[0] << "," << vect[1] << "}";
		return (os);
	}

	int		operator[](unsigned int index) const {
		if (index == 0)
			return (x);
		else
			return (y);
	}
	int		&operator[](unsigned int index) {
		if (index == 0)
			return (x);
		else
			return (y);
	}
	
	vect2	operator++() {
		x++;
		y++;
		return (*this);
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

	vect2	operator+(const vect2 &oth_v) const {
		return (vect2(x + oth_v.x, y + oth_v.y));
	}
	vect2	operator-(const vect2 &oth_v) const {
		return (vect2(x - oth_v.x, y - oth_v.y));
	}
	vect2	operator-() {
		x = -x;
		y = -y;
		return *this;
	}
	
	vect2	&operator+=(const vect2 v){
		*this = *this + v;
		return (*this);
	}
	vect2	operator-=(const vect2 v) {
		*this = *this - v;
		return (*this);
	}

	vect2	operator*(int s) const {
		return (vect2(x * s, y * s));
	}
	friend	vect2	operator*(int s, const vect2 &v) {
		return (vect2(v.x * s, v.y * s));
	}
	
	vect2	operator*=(int s) {
		*this = *this * s;
		return (*this);
	}

	bool	operator==(const vect2 &v) {
		return ((x == v.x) && (y == v.y));
	}
	bool	operator!=(const vect2 &v) {
		return ((x != v.x) || (y != v.y));
	}
};