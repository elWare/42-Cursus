/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:39:51 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/20 12:29:42 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <cstdlib>

class bigint {
	private:
		std::string	val;
		void	removezero() {
			while (val.size() > 1 && val[0] == '0')
				val.erase(0, 1);
		}

	public:
		bigint() : val("0") {}
		bigint(const bigint &oth) : val(oth.val) {}
		bigint(std::string	n_val) : val(n_val) { removezero();}
		bigint(unsigned int numb) {
			std::ostringstream	os;
			
			os << numb;
			val = os.str();
		}
		~bigint() {}

		friend	std::ostream &operator<<(std::ostream &os, const bigint &bi) {
			os << bi.val;
			return os;
		}
		bigint	operator+(const bigint &oth) const {
			std::string	result;
			std::string	op01 = val;
			std::string	op02 = oth.val;
			int			sum = 0;
			int			carry = 0;
			while (op01.size() < op02.size())
				op01 = "0" + op01;
			while (op01.size() > op02.size())
				op02 = "0" + op02;
			for (int i = op01.size() - 1; i >=0; i--)
			{
				sum = (op01[i] - '0') + (op02[i] - '0') + carry;
				carry = sum / 10;
				sum = sum % 10;
				result.insert(result.begin(),  sum + '0');
			}
			if (carry)
				result.insert(result.begin(), (carry + '0'));
			bigint res(result.c_str());
			res.removezero();
			return res;
		}
		
		bigint operator+=(const bigint &n_bi) {
			*this = *this + n_bi;
			return (*this);
		}
		bigint operator++() {
			*this = *this + bigint("1");
			return (*this);
		}
		bigint operator++(int) {
			bigint	tmp = *this;

			*this = *this + bigint("1");
			return tmp;
		}

		bigint	operator<<(unsigned int shift) const {
			if (val == "0")
				return bigint(0);
			return (bigint(val + std::string(shift, '0')));
		}
		bigint	operator<<=(unsigned int shift) {
			*this = *this << shift;
			return (*this);
		}
		bigint operator>>(unsigned int shift) const {
			if (shift >= val.size())
				return (bigint("0"));
			bigint re (val.substr(0, val.size() - shift));
			re.removezero();
			return (re);
		}
		bigint	operator>>=(unsigned int shift) {
			*this = *this >> shift;
			return (*this);
		}
		bigint	operator>>=(const bigint &n_bi) {
			char	*endp;
			unsigned long int	shift = strtoul(n_bi.val.c_str(),&endp, 10);
			if (*endp == '\0')
				*this = *this >> shift;
			return (*this);
		}
		
		bool	operator<(const bigint o_bi) const {
			if (val.size() != o_bi.val.size())
				return (val.size() < o_bi.val.size());
			return (val < o_bi.val);
		}
		bool	operator>(const bigint o_bi) const {
			if (val.size() != o_bi.val.size())
				return (val.size() > o_bi.val.size());
			return (val > o_bi.val);
		}
		bool	operator==(const bigint o_bi) const {
			if (val.size() != o_bi.val.size())
				return false;
			return (val == o_bi.val);
		}
		bool	operator!=(const bigint o_bi) const {
			return !(*this == o_bi);
		}

		bool	operator>=(const bigint o_bi) const {
			return !(*this < o_bi);
		}
		bool	operator<=(const bigint o_bi) const {
			return !(*this > o_bi);
		}
};