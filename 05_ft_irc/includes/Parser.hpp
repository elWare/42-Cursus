/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:30:44 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 11:27:51 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

# include <iostream>
# include <string>
# include <vector>
# include <sstream>

# include "./IRCMessage.hpp"

// PARSER CLASS
// Static IRC message parser. No instantiation required.
class Parser
{
	public:
		// === MAIN ===		
		static IRCMessage parse(const std::string& rawMessage);

		// === HELPER METHODS ===
		static std::vector<std::string> split(const std::string& str, char delimiter);

	private:
		// === CONSTRUCTORS AND DESTRUCTOR ===
		Parser(void);
		Parser(const Parser &instance);
		Parser& operator= (const Parser &instance);
		~Parser(void);

		// === INTERNAL METHODS ===
        static std::string toUpper(const std::string& str);
        static std::string trim(const std::string& str);        	
};

#endif

/*
** PARSER CLASS - Static IRC Message Processor
** ===============================================================================
** A stateless utility class responsible for decomposing raw incoming network 
** streams into structured IRCMessage objects according to RFC 2812 grammar.
**
** PARSING LOGIC:
** --------------
** 1. Tokenization: Splits the raw string into tokens using space delimiters, 
** respecting the protocol's unique handling of the 'trailing' parameter.
** 2. Prefix Extraction: Identifies if the message starts with a colon (':'), 
** isolating the source (server or user identity).
** 3. Command Identification: Extracts the IRC verb (e.g., NICK, JOIN, KICK).
** 4. Parameter Mapping: Aggregates standard arguments into a vector while 
** treating any data following a colon (:) as a single 'trailing' string.
**
** COMPONENT BREAKDOWN EXAMPLE:
** ----------------------------
** Raw Input: ":John!j@host PRIVMSG #lobby :Hello everyone!"
** ┌─────────┬───────────┬─────────┬──────────────────┐
** │ PREFIX  │  COMMAND  │ PARAMS  │     TRAILING     │
** ├─────────┼───────────┼─────────┼──────────────────┤
** │ :John...│  PRIVMSG  │ #lobby  │ Hello everyone!  │
** └─────────┴───────────┴─────────┴──────────────────┘
**
** DESIGN PATTERN:
** ---------------
** - Static Interface: No instantiation required (Static Factory Pattern).
** - Efficiency: Performs single-pass string analysis to minimize overhead 
** during high-frequency message processing.
** - Robustness: Handles malformed inputs, such as empty messages or 
** incorrectly placed delimiters, without crashing the server.
**
** @note This class is strictly for translation; it does not execute commands 
** or validate user permissions (handled by CommandExecutor).
*/
