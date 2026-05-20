#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

class bigint {
	private:
		std::string value;
		void remove_zero() {
			while (value.length() > 1 && value[0] == '0')
				value.erase(0, 1);
		}
	
	public:
		bigint() : value("0") {}
		bigint(const std::string &other) : value(other) {
			remove_zero();
		}
		bigint(unsigned long long other) {
			std::ostringstream os;

			os << other;
			value = os.str();
		}
		~bigint() {}
	
	bigint	operator+(const bigint &other) const {
		std::string	result;
		std::string	val01 = this->value;
		std::string	val02 = other.value;
		int		carry = 0;
		int		sum = 0;

		while (val01.size() < val02.size())
			val01 = '0' + val01;
		while (val01.size() > val02.size())
			val02 = '0' + val02;
		for ( int i = val01.size() - 1; i >= 0; i--)
		{
			sum = (val01[i] - '0') + (val02[i] - '0') + carry;
			carry = sum / 10;
			sum = sum % 10;
			result.insert(result.begin(), '0' + sum);
		}
		if (carry) { 
			result.insert(result.begin(), '0' + carry);
		}
		bigint res(result);
		res.remove_zero();
		return (res);
	}
	bigint	operator+=(const bigint &other) {
		*this = *this + other;
		return (*this);
	}
	bigint	operator++() {
		*this = *this + bigint("1");
		return (*this);
	}
	bigint	operator++(int) {
		bigint	tmp = *this;
		++(*this);
		return (tmp);
	}
	
	bigint	operator<<(int shift) const {
		if (value == "0") 
			return (bigint("0"));
		return (bigint(value + std::string(shift, '0')));
	}
	bigint	operator>>(size_t shift) const {
		bigint	result;

		if (shift >= this->value.size())
			return (bigint("0"));
		result.value = this->value.substr(0, value.size() - shift);
		result.remove_zero();
		return (result);
	}
	bigint	operator<<=(size_t shift) {
		*this = *this << shift;
		return (*this);
	}
	bigint	operator>>=(size_t shift) {
		*this = *this >> shift;
		return (*this);
	}
	bigint	operator>>=(const bigint &oth) {
		char *endptr;
		int	shift = strtol(oth.value.c_str(), &endptr, 10);
		if (*endptr == '\0')
			*this = *this >> shift;
		return *this;
	}

	// operadores lógicos
	bool	operator<(const bigint &oth){
		if (value.size() != oth.value.size())
			return (value.size() < oth.value.size());
		return (value < oth.value);
	}
	bool	operator>(const bigint &oth) {
		if (value.size() != oth.value.size())
			return (value.size() > oth.value.size());
		return (value > oth.value);
	}
	bool	operator<=(const bigint &oth) {
		return !(*this > oth);
	}
	bool	operator>=(const bigint &oth) {
		return !(*this < oth);
	}
	bool	operator==(const bigint &oth) {
		return (value == oth.value);
	}
	bool	operator!=(const bigint &oth) {
		return (value != oth.value);
	}
	friend	std::ostream &operator<<(std::ostream &os, const bigint &oth) {
		os << oth.value;
		return (os);
	}
};
