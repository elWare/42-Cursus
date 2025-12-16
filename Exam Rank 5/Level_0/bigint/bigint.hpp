#pragma once
#include <string>
#include <iostream>

class bigint {
	private:
		std::string num;
		void remove_zeros()
		{
			while(num.length() > 1 && num[0] == '0')
				num.erase(0, 1);
		}

	public:
		bigint() : num("0") {}
		bigint(const std::string &n) : num(n){ remove_zeros();}
		bigint(unsigned int n) : num(std::to_string(n)) {}

	bigint operator+(const bigint &other) const 
	{
		std::string result;
		std::string n1 = num;
		std::string n2 = other.num;
		while (n1.length() < n2.length())
			n1 = '0' + n1;
		while (n2.length() < n1.length())
			n2 = '0' + n2;
		int carry = 0;
		for (int i = n1.length() - 1; i >= 0; --i) {
			int digit_sum = (n1[i] - '0') + (n2[i] - '0') + carry;
			carry = digit_sum / 10;
			result = char((digit_sum % 10) + '0') + result;
		}
		if (carry)
			result = char(carry + '0') + result;
		return bigint(result);
	}
	bigint	&operator+=(const bigint &other)
	{
		*this = *this + other;
		return *this;
	}

	bigint	&operator++()
	{
		*this = *this + bigint("1");
		return *this;
	}
	bigint	operator++(int)
	{
		bigint temp = *this;
		++(*this);
		return temp;
	}

// shifter operator ------------------------------------------------------
	bigint	operator<<(int shift) const
	{
		if (num == "0")
			return *this;
		return (bigint(num + std::string(shift, '0')));
	}
	bigint	&operator>>(int shift)
	{
		if (shift >= (int)num.length())
			num = "0";
		else
		{
			num = num.substr(0, num.length() - shift);
			remove_zeros();
		}
		return *this;
	}
	bigint &operator<<=(int shift) { *this = *this << shift; return *this; }
	bigint &operator>>=(int shift) { *this = *this >> shift; return *this; }
	bigint &operator>>=(const bigint &oth) { 
		int shift = std::stoi(oth.num); *this = *this >> shift; return *this; }

// logical operator 
	bool operator== (const bigint &other) const
	{
		return (num == other.num);
	}
	bool operator!= (const bigint &other) const
	{
		return !(num == other.num);
	}
	bool	operator<(const bigint &other) const
	{
		if (num.length() != other.num.length())
			return (num.length() < other.num.length());
		return (num < other.num);
	}
	bool	operator<=(const bigint &other) const
	{
		return (*this < other || *this == other);
	}
	bool	operator>(const bigint &other) const
	{
		return !(*this < other);
	}
	bool	operator>=(const bigint &other) const
	{
		return !(*this <= other);
	}
// output operator ------------------------------------------------------
	friend std::ostream &operator<<(std::ostream &os, const bigint &b) { os << b.num; return os; }
};