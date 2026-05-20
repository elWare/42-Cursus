/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:03:59 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 12:15:22 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/IRCMessage.hpp"

// === CONSTRUCTORS AND DESTRUCTOR ===

/**
 * @brief Default constructor for IRCMessage DTO.
 * Instantiates completely blank string values tracking message prefixes, commands and parameters.
 */
IRCMessage::IRCMessage(void)
    :	_rawMessage(""),
        _prefix(""), _command(""), _trailing("")
{ }

/**
 * @brief Destructor safely handling container purging bounding Response sets and mapping parameters blocks.
 */
IRCMessage::~IRCMessage(void)
{	
    _params.clear();	
    _responses.clear();			
}

// === MAIN CONST PARAM ===	

/**
 * @brief Parameterized constructor preserving unmodified exact sequences mapped by client sockets.
 * 
 * @param rawMessage Non-destructed raw sequences bypassing any text parsers validating initial payloads.
 */
IRCMessage::IRCMessage(const std::string &rawMessage)
    :	_rawMessage(rawMessage),
        _prefix(""), _command(""), _trailing("")
{ }

// === SETTERS ===

/**
 * @brief Interface for accessing and modifying the internal components of an IRC message.
 * * Data Management Flow:
 * 1. State Encapsulation: Provides controlled access to the four pillars of 
 * an IRC message: Prefix (source), Command (verb), Parameters (targets/flags), 
 * and Trailing (data/content).
 * 2. Prefix & Command Handling: Allows the parser to bind the identified 
 * source and the protocol action to the message object.
 * 3. Parameter Stacking: Enables the incremental building of the argument 
 * vector, supporting commands with multiple targets (e.g., JOIN #a,#b).
 * 4. Trailing Integrity: Manages the final 'long' parameter, ensuring the 
 * leading colon (:) is handled as a delimiter and not part of the content.
 * * @note Getters are marked as 'const' to guarantee read-only access during 
 * the command execution phase, preventing accidental state corruption.
 */

void IRCMessage::setPrefix(const std::string &prefix)
{
    this->_prefix = prefix;
}

void IRCMessage::setCommand(const std::string &command)
{
    this->_command = command;
}

void IRCMessage::addParam(const std::string &param)
{
    this->_params.push_back(param);
}

void IRCMessage::setTrailing(const std::string &trailing)
{
    this->_trailing = trailing;
}

// === GETTERS ===

const std::string&	IRCMessage::getPrefix(void)	const
{
    return (this->_prefix);
}

const std::string&	IRCMessage::getCommand(void) const
{
    return (this->_command);
}

const std::vector<std::string>&	IRCMessage::getParams(void) const
{
    return (this->_params);
}

const std::string&	IRCMessage::getTrailing(void) const
{
    return (this->_trailing);
}

// === BIDIRECTIONAL METHODS === 

/**
 * @brief Embeds generated outbound packages assigning arrays mapping specific targeting FDs.
 * 
 * Execution Steps:
 * 1. Confirms target matrix limits asserting at least one recipient identifier maps.
 * 2. Transcribes explicit target indexes pushing values into logical Response DTO instances.
 * 3. Enforces standard protocol bindings assuring trailing configurations conclude bounding RFC compliant (\r\n) formats safely.
 * 4. Pushes validated configurations safely mapped into internal transmission vectors.
 * 
 * @param targetFds Collection representing destination tracking limits mapping identified clients expecting broadcasts.
 * @param message String representation containing translated string sequences prepared routing.
 */
void	IRCMessage::addResponse(const std::vector<int>& targetFds, const std::string& message)
{
    if  (targetFds.empty())
        return ;

    Response response;
    response.targetFds = targetFds;			

    if (message.size() < 2 || message.substr(message.size() - 2) != CRLF)
        response.text = message + CRLF;
    else
        response.text = message;

    _responses.push_back(response);	
}

// === READING ANSWERS METHOD === 

const std::vector<Response>&	IRCMessage::getResponses(void) const
{
    return (this->_responses);
}

// === STATIC FORMATTING METHODS (RFC 2812) === 	

/**
 * @brief Constructs an explicit mapping format establishing proper RFC Server notification sequences.
 * Example Formats tracking server codes (001, 403, 461...): 
 * [:serverName] [code] [nickname] [optional_param] [:message]
 * 
 * @param serverName Bound server textual instance matching configurations routing sequence origin contexts.
 * @param nickname User specific tracking descriptor mapping message target dependencies.
 * @param code Distinct identification block mapping standard numerical RFC designations routing states.
 * @param message Description mapping textual blocks translated to end user screens validating status updates.
 * @param param Dynamically optional parameter targeting precise command structures responding mapped actions.
 * @return Concatenated continuous string mapped correctly routing compliant structures.
 */
std::string IRCMessage::buildServerMessage(const std::string& serverName, const std::string& nickname, 
        const std::string& code, const std::string& message, const std::string& param)
{
    std::string	formatMsg;
    
    if (param.empty())
        formatMsg = ":" + serverName + " " + code + " " + nickname + " " + message;
    else
        formatMsg = ":" + serverName + " " + code + " " + nickname + " " + param + " " + message;
    return (formatMsg);
}

/**
 * @brief Constructs compliant routing format establishing explicit message redirections mapping client instances.
 * Example Formats forwarding sequences bridging multiple connected endpoints: 
 * [:prefix] [command] [parameters]
 * 
 * @param prefix Fully mapped identity matrix extracting valid origins generating strings (nick!user@host).
 * @param command Validated operational designation targeting defined commands parsed safely.
 * @param params Associated sequence trailing arrays routing targeted executions correctly mapped.
 * @return Complete textual mapped combinations simulating original network origins mapping destinations cleanly.
 */
std::string IRCMessage::buildClientMessage(const std::string& prefix, const std::string& command, const std::string& params)
{
    std::string	formatMsg = ":" + prefix + " " + command + " " + params;
    return (formatMsg);
}

// === UTILITIES ===

/**
 * @brief Utility methods for lifecycle management and structural analysis of IRC messages.
 * * Operational Logic:
 * 1. Parameter Quantification (paramCount): 
 * - Provides an O(1) complexity check for the number of arguments stored.
 * - Used primarily by the CommandExecutor to trigger ERR_NEEDMOREPARAMS (461) 
 * before executing command-specific logic.
 * 2. Object Reset (clearMessage):
 * - Performs a full cleanup of the internal state, clearing the prefix, 
 * command, parameter vector, and trailing string.
 * - Essential for object recycling in high-performance scenarios, ensuring 
 * that no data from a previous socket read "leaks" into the next message 
 * parsing cycle.
 * * @note clearMessage() is a critical safeguard for memory integrity when 
 * reusing IRCMessage instances within the same connection buffer.
 */

size_t IRCMessage::paramCount(void) const
{
    return (_params.size());
}

void	IRCMessage::clearMessage(void)
{
    _prefix.clear();
    _command.clear();	
    _params.clear();
    _trailing.clear();
}

/**
 * @brief Debug visualizer presenting explicitly captured structures identifying 
 * segmented fields translating DTO mappings.
 */
void 	IRCMessage::printParsedMessage(void)
{
    std::cout << std::endl << "Prefix: \t <" << _prefix 	<< ">" << std::endl;
    std::cout << "Command: \t " 	<< _command	<< std::endl;
    std::cout << "Params: \t [";
    for (size_t index = 0; index < _params.size(); index++)
    {
        std::cout << _params[index];
        if ((index + 1) < _params.size())
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout << "Trailing: \t <" 	<< _trailing << ">" << std::endl;
}
