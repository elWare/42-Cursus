/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:03:33 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 12:14:16 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCMESSAGE_HPP
#define IRCMESSAGE_HPP

# include <iostream>
# include <string>
# include <vector>

# define IRC_MESSAGE_ID				"[IrcMessage] \t"
# define CONSTRUCTOR_MSG    		"Default Constructor: object created.\t"
# define COPY_CONSTRUCTOR_MSG		"Copy Constructor: object created.\t"
# define ASSIGNMENT_MSG				"Assignment operator: obj created.\t"
# define DESTRUCTOR_MSG	    		"Destructor: object destroyed.\t"
# define PARAM_CONSTRUCTOR_MSG		"Parametric Constructor: object created."

# define CRLF						"\r\n"

// Message grouping structure (output + recipients).
// Allows a single text to be sent to multiple FDs (e.g., broadcast on a channel).
struct Response
{
	std::vector<int> 	targetFds;
	std::string 		text;
};

// "Smart Object" -> will act as a bidirectional DTO (Data Transfer Object) -> (Bidirectional DTO Pattern)
// Outbound trip -> contains what the client wrote (Data Request).
// Return trip -> contains the list of responses and to whom they should be sent (Data Response).
class IRCMessage
{
	public:
		// === CONSTRUCTORS AND DESTRUCTOR ===
		IRCMessage(void);
		~IRCMessage(void);

		// === MAIN CONST PARAM ===	
		IRCMessage(const std::string &rawMessage);

		// === SETTERS ===
		void setPrefix(const std::string &prefix);
		void setCommand(const std::string &command);
		void addParam(const std::string &param);
		void setTrailing(const std::string &trailing);

		// === GETTERS ===
		const std::string&				getPrefix(void)	const;
		const std::string& 				getCommand(void) const;
		const std::vector<std::string>& getParams(void) const;
		const std::string& 				getTrailing(void) const;

		// === BIDIRECTIONAL METHODS === 	
		void	addResponse(const std::vector<int>& fds, const std::string& responseMsg);

		// === READING ANSWERS METHOD === 
		const std::vector<Response>&	getResponses(void) const;

		// === STATIC FORMATTING METHODS (RFC 2812) === 
		std::string buildServerMessage(const std::string& serverName, const std::string& nickname, 
				const std::string& code, const std::string& message, const std::string& param = "");

		std::string buildClientMessage(const std::string& prefix, const std::string& command, const std::string& params);

		// === UTILITIES ===
		size_t 	paramCount(void) const;		
		void	clearMessage(void);
		void 	printParsedMessage(void);

	private:
		// === REQUEST -> INPUT DATA ===	
		std::string					_rawMessage;

		std::string					_prefix;
		std::string					_command;
		std::vector<std::string> 	_params;
		std::string					_trailing;

		// === RESPONSE -> OUTPUT DATA ===	
		std::vector<Response> 		_responses;		
};

#endif

/*
** ==========================================================================
** IRC MESSAGE
** ==========================================================================
**
** Format of an IRC message (according to RFC 1459/2812):
** ------------------------------------------------------
**
** [:prefix] <command> [param1] [param2] ... [:trailing]
**
** Where:
** - prefix:   (Optional) Message origin. Starts with ':'
**             Example: ":nick!user@host"
** - command:  The IRC command (NICK, JOIN, PRIVMSG, etc.)
** - params:   Command parameters separated by spaces
** - trailing: (Optional) Last parameter, can contain spaces.
**             Starts with ':' in the parameter position.
**
** EXAMPLES:
** ---------
** "NICK pepe"
**   → command: NICK, params: ["pepe"]
**
** "PRIVMSG #general :Hello everyone!"
**   → command: PRIVMSG, params: ["#general", "Hello everyone!"]
**
** ":pepe!user@host PRIVMSG #42 :Message with spaces"
**   → prefix: "pepe!user@host", command: PRIVMSG,
**     params: ["#42", "Message with spaces"]
**
** "JOIN #channel1,#channel2"
**   → command: JOIN, params: ["#channel1,#channel2"]
**
** "USER username 0 * :Real Name"
**   → command: USER, params: ["username", "0", "*", "Real Name"]
**
** "JOIN #canal1,#canal2"
**   → command: JOIN, params: ["#canal1,#canal2"]
**
** "USER username 0 * :Real Name"
**   → command: USER, params: ["username", "0", "*", "Real Name"]**
*/
