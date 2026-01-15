/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:32:48 by jumarque          #+#    #+#             */
/*   Updated: 2026/01/15 19:16:52 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <ostream>
#include <sstream>

class bigint {
	private:
		std::string	val;
		void removezero() {
			while (val.size() > 1 && val[0] == '0')
				val.erase(0, 1);
		}
	public:
		bigint() : val("0") {}
		bigint(const std::string &n_val) : val(n_val) { removezero(); }
		bigint(const bigint &n_bi) : val(n_bi.val) {}
		bigint(long long int num) {
			std::ostringstream	os;
			os << num;
			val = os.str();
		}

		friend	std::ostream &operator<<(std::ostream &os, const bigint n_bi) {
			os << n_bi.val;
			return (os);
		}
		
		bigint	operator+(const bigint oth_bi) const {
			std::string	result;
			std::string	op01 = val;
			std::string	op02 = oth_bi.val;
			int			sum = 0;
			int			carry = 0;

			while (op01.size() < op02.size())
				op01 = '0' + op01;
			while (op02.size() < op01.size())
				op02 = '0' + op02;
			for (int i = op01.size() - 1; i >= 0; i--) {
				sum = ((op01[i] - '0') + (op02[i] - '0') + carry);
				carry = sum / 10;
				sum = sum % 10;
				result.insert(result.begin(), (sum + '0'));
			}
			if (carry)
				result.insert(result.begin(), (carry + '0'));
			bigint	res(result);
			res.removezero();
			return (res);
		}
		
		bigint	operator+=(const bigint	&oth_bi) {
			*this = *this + oth_bi;
			return (*this);
		}
		bigint	operator++() {
			*this = *this + bigint("1");
			return (*this);
		}
		bigint	operator++(int) {
			bigint	tmp = *this;

			*this = *this + bigint("1");
			return (tmp);
		}
		bigint	operator<<(const int &shift) {
			if (val != "0")
				val = val + std::string(shift, '0');
			return (*this);
		}
		bigint	operator<<=(const int &shift) {
			if (val != "0")
				*this = *this << shift;
			return (*this);
		}
		bigint	operator>>(const int &shift) {
			bigint	result;
			if ((unsigned long int)shift >= val.size())
				return (bigint("0"));
			result.val = val.substr(0, val.size() - shift);
			result.removezero();
			return (result);
		}
		bigint	operator>>=(const int &shift) {
			*this = *this >> shift;
			return (*this);
		}
		bigint	operator>>=(const bigint &oth_bi) {
			char	*endp;
			unsigned long long int shift = strtoull(oth_bi.val.c_str(), &endp, 10);

			if (*endp == '\0')
				*this = *this >> shift;
			return (*this);
		}

		bool	operator<(const bigint	&oth_bi) {
			if (val.size() != oth_bi.val.size())
				return (val.size() < oth_bi.val.size());
			return (val < oth_bi.val);
		}
		bool	operator<=(const bigint &oth_bi) {
			return !(*this > oth_bi);
		}
		bool	operator>(const bigint &oth_bi) {
			if (val.size() != oth_bi.val.size())
				return (val.size() > oth_bi.val.size());
			return (val > oth_bi.val);
		}
		bool	operator>=(const bigint &oth_bi) {
			return !(*this < oth_bi);
		}
		bool	operator==(const bigint &oth_bi) {
			if (val.size() != oth_bi.val.size())
				return false;
			return (val == oth_bi.val);
		}
		bool	operator!=(const bigint &oth_bi) {
			return (val != oth_bi.val);
		}
		
};