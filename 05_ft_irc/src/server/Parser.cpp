/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:30:35 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/12 21:09:11 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Parser.hpp"

// === MAIN ===

/**
 * @brief Parses a raw IRC message adhering to the RFC 1459/2812 formats.
 * Expected format: [:prefix] <command> [param1] [param2] ... [:trailing]
 * 
 * Execution Flow / Algorithm:
 * 1. Sanitizes the message by trimming spaces and carriage returns.
 * 2. Parses the optional PREFIX: 
 *    - If the string starts with ':', extracts the token up to the first space as the origin of the message.
 * 3. Parses the COMMAND:
 *    - Extracts the next immediate token. Always converted to UPPERCASE for uniform comparisons.
 * 4. Parses the PARAMS and TRAILING:
 *    - Tokens separated by spaces are captured individually and pushed into the param vector.
 *    - If a parameter begins with ':', everything strictly following it (including spaces) 
 *      is captured as a single final TRAILING parameter (message body).
 * 
 * @param rawMessage The plain text string read directly from the network buffer.
 * @return An IRCMessage Data Transfer Object populated with parsed prefix, command, trailing, and parameters.
 */
IRCMessage Parser::parse(const std::string& rawMessage)
{
    IRCMessage 	ircMessage;
    std::string	msg;
    size_t		position = 0;
    size_t 		spacePosition;

    msg = trim(rawMessage);
    if (msg.empty())
        return (ircMessage);

    if (msg[position] == ':')
    {
        spacePosition = msg.find(' ', position);	
        if (spacePosition == std::string::npos)		
            return (ircMessage);
        
        std::string	prefix = msg.substr(1, spacePosition - 1);
        ircMessage.setPrefix(prefix);

        position = msg.find_first_not_of(' ', spacePosition);	
    }

    if (position == std::string::npos)
        return (ircMessage);						
    
    std::string command;

    spacePosition = msg.find(' ', position);		
    if (spacePosition == std::string::npos)			
    {
        command = msg.substr(position);		
        command = Parser::toUpper(command);
        ircMessage.setCommand(command);
        return (ircMessage);
    }	
    
    command = msg.substr(position, (spacePosition - position));
    command = Parser::toUpper(command);
    ircMessage.setCommand(command);

    position = msg.find_first_not_of(' ', spacePosition);		

    while (position != std::string::npos)
    {
        if (msg[position] == ':')
        {
            std::string trailing = msg.substr(position + 1);
            ircMessage.setTrailing(trailing);
            break ;
        }
        
        std::string param;

        spacePosition = msg.find(' ', position);
        if (spacePosition == std::string::npos)		
        {
            param  = msg.substr(position);
            ircMessage.addParam(param);
            break ;
        }

        param = msg.substr(position, (spacePosition - position));
        ircMessage.addParam(param);

        position = msg.find_first_not_of(' ', spacePosition);	 
    }    
    return (ircMessage);
}

// === HELPER METHODS ===

/**
 * @brief Splits a string by a given delimiter character.
 * Utilizes string stream to sequentially extract blocks. Empty tokens are discarded.
 * 
 * @param str The payload string to split.
 * @param delimiter The character specifying bounds for extraction.
 * @return A sequence subset vector populated with extracted block tokens.
 */
std::vector<std::string> Parser::split(const std::string& str, char delimiter)
{
    std::vector<std::string>	tokens;
    std::string					token;
    std::istringstream			tokenStream(str);

    while (std::getline(tokenStream, token, delimiter))
    {
        if (token.empty())
            break ;
        tokens.push_back(token);
    }
    return (tokens);
}

// === PRIVATE CONSTRUCTORS AND DESTRUCTOR === 

Parser::Parser(void)	
{ }

Parser::Parser(const Parser &instance)
{ (void) instance; }

Parser& Parser::operator= (const Parser &instance)
{ 
    (void) instance;
    return (*this);
}

Parser::~Parser(void)
{ }

// === PRIVATE INTERNAL METHODS ===

/**
 * @brief Converts a given string fully to UPPERCASE.
 * Necessary because IRC commands are strictly case-insensitive according to RFC standards.
 * 
 * @param str String target for conversion.
 * @return A new converted instance string mapped entirely in uppercase.
 */
std::string Parser::toUpper(const std::string& str)
{
    std::string	upperStr = str;

    for (size_t index = 0; index < upperStr.length(); index++)
        upperStr[index] = std::toupper(upperStr[index]);
    return (upperStr);
}

/**
 * @brief Strips leading and trailing white spaces and control characters based on RFC standard sets.
 * Cleans the boundaries using standard delimiter properties (" \t\n\r\v\f").
 * 
 * @param str Reference string intended for boundary sanitation.
 * @return The sub string component strictly absent of trailing/leading padding.
 */
std::string Parser::trim(const std::string& str)
{	
    if (str.empty())									
        return ("");
    
    std::string			trimString;
    const std::string 	whiterSpace = " \t\n\r\v\f";	
    
    size_t start = str.find_first_not_of(whiterSpace);	
    if (start == std::string::npos) 
        return (""); 
    size_t end = str.find_last_not_of(whiterSpace);	
    
    trimString = str.substr(start, (end - start) + 1);	
    return (trimString);
}
