/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:45:14 by jumarque          #+#    #+#             */
/*   Updated: 2026/02/06 17:27:27 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define PURPLE "\033[0;35m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

#define FILE "./data.csv"

#define DATE_ERR "Error: incorrect data => "
#define YEAR_ERR "Error: year is not at the database => "
#define MONTH_ERR "Error: incorrect month => "
#define DAY_ERR "Error: incorrect day => "
#define BUYS_ERR "Error: invalid acquisition => "
#define POSITIVE_ERR "Error: not a positive number."
#define LARGE_ERR "Error: too large number."

#define BAD_ARG "Error: bad number of arguments"
#define INPUT_ERR "Error: bad input => "
#define OPEN_ERR_FILE "Error: could not open file"
#define OPEN_ERR_DB "Error: cannot open database"

class BitcoinExchange {
	private:
		std::map<std::string, float> _bitcoinPrice;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &oth);
		BitcoinExchange	operator=(const BitcoinExchange &oth);
		~BitcoinExchange();

		void	readData(std::ifstream &fd);
		float	getBitcoinPrice(const std::string date);
		bool isDateFormatValid(const std::string &date);
		bool isValidDate(const std::string &date);
		bool isDataInRange(const std::string &rate);
};