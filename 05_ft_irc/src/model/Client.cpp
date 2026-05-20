/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:10:44 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 11:44:30 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Client.hpp"

// === CONSTRUCTORS AND DESTRUCTOR ===

/**
 * @brief Default constructor for Client.
 * Initializes default network states, file descriptor sets to -1, and boolean flags reset to false.
 */
Client::Client(void)
    :	_fd(-1), _ip(""),
        _inputBuffer(""), _outputBuffer(""),
        _nickname("*"), _username(""), _realname(""),
        _hasPassword(false), _hasNick(false), _hasUser(false),
        _isOperator(false)
{ }

/**
 * @brief Parameterized constructor mapping active connections to new model states.
 * Connects standard defaults except the nickname, which asserts to the standard '*' IRC marker identifying "unnamed" clients.
 * 
 * @param fd Number designating socket tracking file descriptor mapped by accepted OS instances.
 * @param ip Text block tracking textual representation formats associated directly with the target socket origin.
 */
Client::Client(int fd, const std::string& ip)
    :	_fd(fd), _ip(ip),
        _inputBuffer(""), _outputBuffer(""),
        _nickname("*"), _username(""), _realname(""),
        _hasPassword(false), _hasNick(false), _hasUser(false),
        _isOperator(false)
{ }

/**
 * @brief Destructor for Client bounds cleanup.
 */
Client::~Client(void)
{ }

// === GETTERS ===

int	Client::getFd(void) const
{
    return (this->_fd);
}

const std::string&	Client::getIp(void)			const
{
    return (this->_ip);
}

const std::string&	Client::getNickname(void) 	const
{
    return (this->_nickname);
}

const std::string&	Client::getUsername(void) 	const
{
    return (this->_username);
}

const std::string&	Client::getRealname(void) 	const
{
    return (this->_realname);
}

const std::string&	Client::getRecvBuffer(void) const
{
    return (this->_inputBuffer);
}

// === STATE GETTERS ===

bool	Client::hasPassword(void) 	const
{
    return (this->_hasPassword);
}

bool	Client::hasNick(void)		const
{
    return (this->_hasNick);
}

bool	Client::hasUser(void)		const
{
    return (this->_hasUser);
}

/**
 * @brief Evaluates client validation verifying standard three-tier registration.
 * Ensures the target user fulfilled required steps before assuming standard permissions: PASS + NICK + USER completion.
 * 
 * @return True if standard boolean progression is passed, False mapping missing context flags restricting command use.
 */
bool	Client::isRegistered(void)	const
{
    return (_hasPassword && _hasNick && _hasUser);
}

bool	Client::isOperator(void)	const
{
    return (this->_isOperator);
}

// === SETTERS ===

void	Client::setNickname(const std::string &nickname)
{
    this->_nickname = nickname;
}

void	Client::setUsername(const std::string &username)
{
    this->_username = username;
}

void	Client::setRealname(const std::string &realname)
{
    this->_realname = realname;
}

void	Client::setHasPassword(bool value)
{
    this->_hasPassword = value;
}

void	Client::setHasNick(bool value)
{
    this->_hasNick = value;
}

void	Client::setHasUser(bool value)
{
    this->_hasUser = value;
}

void	Client::setOperator(bool value)
{
    this->_isOperator = value;
}

// === BUFFER HANDLING ===

void	Client::appendToBuffer(const std::string &data)
{
    this->_inputBuffer += data;
}

void	Client::clearBuffer(void)
{
    this->_inputBuffer.clear();
}

/**
 * @brief Analyzes string accumulation matching protocol delimitations extracting one single full message from buffer pools.
 * 
 * Execution Steps:
 * 1. Checks strictly compliant instances locating explicit trailing patterns mapped matching ('\r\n').
 *    - Extracted component is separated omitting delimitation markers. Total bound is erased adjusting memory buffer sequence.
 * 2. Employs secondary non-standard compatibility validation designed assisting non-conforming telnet/netcat client streams ending with ('\n').
 *    - Extra cleaning removes carriage return mismatches handling partial delimiter splitting.
 * 3. Safely returns empty instances signifying unfulfilled command completion sequences prompting server loop idle cycles.
 * 
 * @return Safely extracted substring targeting isolated individual commands. Returns empty formatting upon incomplete matches.
 */
std::string	Client::extractRawMessage(void)
{	
    std::string 			rawMessage = "";
    std::string::size_type	position;
    
    position = _inputBuffer.find("\r\n");    
    if (position != std::string::npos)
    {
        rawMessage = _inputBuffer.substr(0, position);    	 
        _inputBuffer.erase(0, position + 2);				       
        return (rawMessage);
    }
    
    position = _inputBuffer.find("\n");
    if (position != std::string::npos)
    {
        rawMessage = _inputBuffer.substr(0, position);
        _inputBuffer.erase(0, position + 1);        

        if (!rawMessage.empty() && rawMessage[rawMessage.length() - 1] == '\r')
            rawMessage.erase(rawMessage.length() - 1);        
        return (rawMessage);
    }    
    
    return (rawMessage);
}

/**
 * @brief Status trigger determining if active un-sent queued packets remain enqueued within client's tracked transmission block mapping.
 * 
 * @return True when tracking arrays confirm data blocks awaiting flush; otherwise False mapping completion/empty context.
 */
bool	Client::hasPendingOutputData(void) const
{
    return (!_outputBuffer.empty());
}

// === MESSAGE SENDING ===

/**
 * @brief Accumulates generated output formatted sequences into local network staging buffer structures triggering tracked polling dependencies targeting Server processes.
 * 
 * @param message Sequential formatted character chunks awaiting network transit targeting designated peers.
 */
void	Client::sendBuffer(const std::string &message)
{
    this->_outputBuffer += message;
}

/**
 * @brief Passively links external process network handling elements fetching enqueued mapping sequences awaiting transmission via socket.
 * 
 * @return Memory reference targeting locally accumulated string formats awaiting network transit via `send()`.
 */
const std::string&	Client::getSendBuffer(void) const
{
    return (this->_outputBuffer);
}

/**
 * @brief Shrinks internal target string sequence actively adjusting tracking vectors upon successful external OS socket stream dispatch confirming safe network handoff.
 * 
 * @param sentBytes Explicit bounds defining exact stream length confirmed handled securely bypassing pending validation checks.
 */
void	Client::eraseSentBytes(size_t sentBytes)
{
    if (sentBytes <= _outputBuffer.size())
        _outputBuffer.erase(0, sentBytes);
}

// === UTILITIES ===

/**
 * @brief Generates proper identity framing sequence mimicking client origin context strictly mapped within formal IRC interactions forwarding states connecting different endpoints (nickname!username@host).
 * 
 * @return Full character sequence mapped mapping formal system identities targeting destination contexts connecting isolated endpoints safely mapped.
 */
std::string	Client::getPrefix(void) const
{
    return (this->_nickname + "!" + this->_username + "@" + this->_ip);	
}

