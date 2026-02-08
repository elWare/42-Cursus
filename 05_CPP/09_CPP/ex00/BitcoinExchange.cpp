/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:05:31 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/08 10:23:05 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	std::cout << "Default Constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &oth) { *this = oth;}
BitcoinExchange BitcoinExchange::operator=(const BitcoinExchange &oth) {
	this->_bitcoinPrice = oth._bitcoinPrice;
	return *this;
}
BitcoinExchange::~BitcoinExchange() {
	std::cout << "Destructor called" << std::endl;
}

float	ft_stof(const std::string &str) {
	float	f_numb;

	std::stringstream ss(str);
	ss >> f_numb;
	return (f_numb);
}

float	BitcoinExchange::getBitcoinPrice(const std::string str){
	if (!isValidDate(str)) {
		std::cerr << RED "Invalid date: " << str << RESET << std::endl;
		return -1.0f;
	}
	if (this->_bitcoinPrice.count(str) > 0)
		return (this->_bitcoinPrice.at(str));
	std::map<std::string, float>::iterator it = this->_bitcoinPrice.lower_bound(str);
	if (it == this->_bitcoinPrice.begin() && str < it->first)
	{
		std::cerr << RED "No data avaible before " << it->first << RESET << std::endl;
		return -1.0f;
	}
	if (it == this->_bitcoinPrice.end()) {
		return (--it)->second;
	}
	return ((--it)->second);
}

bool BitcoinExchange::isDateFormatValid(const std::string &date) {
	if (date.empty()) {
		std::cerr << DATE_ERR << "empty date" << std::endl;
		return false;
	}
	return (true);
}
bool	BitcoinExchange::isValidDate(const std::string &date) {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
		std::cerr << "Aquí " <<RED DATE_ERR << "\"" << date << "\"" << RESET << std::endl;
		return (false);
	}

	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	for (size_t i = 0; i < yearStr.size(); i++) {
		if (!isdigit(yearStr[i])){
			std::cerr << RED YEAR_ERR << "\"" << date << "\"" << RESET << std::endl;
			return false;
		}
	}

	for (size_t i = 0; i < monthStr.size(); i++) {
		if (!isdigit(monthStr[i])){
			std::cerr << RED MONTH_ERR << "\"" << date << "\"" << RESET << std::endl;
			return false;
		}
	}
	
	for (size_t i = 0; i < dayStr.size(); i++) {
		if (!isdigit(dayStr[i])){
			std::cerr << RED DAY_ERR << "\"" << date << "\"" << RESET << std::endl;
			return false;
		}
	}
	
	int year, month, day;
	std::stringstream(yearStr) >> year;
	std::stringstream(monthStr) >> month;
	std::stringstream(dayStr) >> day;

	if (year < 2009) {
			std::cerr << RED << YEAR_ERR << year << RESET << std::endl;
		return false;
	}
	
	if (month < 1 || month > 12) {
		std::cerr << RED << MONTH_ERR << month << RESET << std::endl;
		return false;
	}

	if (day < 1 || day > 31
	|| (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11))
	|| (day > 29 && month == 2) || (day > 28 && month == 2 && (year % 4 != 0
	|| (year % 100 == 0 && year % 400 != 0)))) {
		std::cerr << RED << DAY_ERR << day << RESET << std::endl;
		return false;
	}

	return true;
}

bool BitcoinExchange::isDataInRange(const std::string &data) {

	if (data.empty() || data.find_last_not_of("0123456789.-") != std::string::npos
	|| data.at(0) == '.' || data.find('.', data.length() - 1) != std::string::npos)
		std::cerr << RED << DATE_ERR << data << RESET << std::endl;
	else if (data.at(0) == '-')
		std::cerr << RED << POSITIVE_ERR << RESET << std::endl;
	else if (data.length() > 10 || (data.length() == 10 && data > "2147483647"))
		std::cerr << RED << LARGE_ERR << RESET << std::endl;
	else
		return true;
	return false;
}


void BitcoinExchange::readData(std::ifstream &file) {

	std::string line;
	size_t pos;
	bool hasHeader = false;

	if (std::getline(file, line)) {
		if (line.find("date") != std::string::npos 
		|| line.find("value") != std::string::npos) {
			hasHeader = true;
		} else {
			pos = line.find(',');
			if (pos != std::string::npos) {
				std::string date = line.substr(0, pos);
				std::string valueStr = line.substr(pos + 1);
				if (isValidDate(date)) {
					float value;
					std::stringstream ss(valueStr);
					if (ss >> value) {
						this->_bitcoinPrice[date] = value;
					} else {
						std::cerr << "Invalid value in data: " << valueStr << std::endl;
					}
				} else {
					std::cerr << "Invalid date in data: " << date << std::endl;
				}
			} else {
				std::cerr << "Invalid line format: " << line << std::endl;
			}
		}
	}
	(void)hasHeader;
	while (std::getline(file, line)) {
		pos = line.find(',');
		if (pos == std::string::npos) {
			std::cerr << "Invalid line format: " << line << std::endl;
			continue;
		}
		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 1);

		if (!isValidDate(date)) {
			std::cerr << "Invalid date in data: " << date << std::endl;
			continue;
		}

		float value;
		std::stringstream ss(valueStr);
		if (!(ss >> value)) {
			std::cerr << "Invalid value in data: " << valueStr << std::endl;
			continue;
		}

		this->_bitcoinPrice[date] = value;
	}
	file.close();

}