/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:34:02 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 12:52:40 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Channel.hpp"

// === CONSTRUCTORS AND DESTRUCTOR ===

/**
 * @brief Default constructor for Channel.
 * Initializes default channel states: standard unprivileged settings, no topic, empty password, 
 * and boolean flags deactivated (invite only, topic restricted, and user limits).
 */
Channel::Channel(void)
    :	_name("default"), _topic(""), _passwordChannel(""),
        _invitedOnly(false), _topicRestricted(false), _userLimit(0)
{ }

/**
 * @brief Destructor for Channel.
 * Safely clears all mapped structures (members, operators, and invitees) tracked by the channel block.
 */
Channel::~Channel(void)
{
    _members.clear();		
    _operators.clear();
    _inviteds.clear();
}

/**
 * @brief Parameterized constructor establishing target configuration contexts matching defined channel name rules.
 * 
 * @param name Formatting sequence used binding identities targeting the newly generated channel map.
 */
Channel::Channel(const std::string &name)
    :	_name(name), _topic(""), _passwordChannel(""),
        _invitedOnly(false), _topicRestricted(false), _userLimit(0)
{ }

/// === GETTER + SETTERS ===

const std::string&	Channel::getName(void)	const
{
    return (this->_name);
}

const std::string&	Channel::getTopic(void)	const
{
    return (this->_topic);
}

void	Channel::setTopic (const std::string &newTopic)
{
    this->_topic = newTopic;
}

const std::string&	Channel::getPassword(void)	const
{
    return (this->_passwordChannel);
}

bool	Channel::hasPasswordChannel(void) const
{
    return (this->_passwordChannel != "");
}

void	Channel::setPasswordChannel (const std::string &newPassword)
{
    this->_passwordChannel = newPassword;
}

// === CHANNEL MODES ===

bool	Channel::isInviteOnly(void) const
{
    return (this->_invitedOnly);
}

void	Channel::setInvitedOnly(bool value)
{
    this->_invitedOnly = value;
}

bool	Channel::isTopicRestricted(void) const
{
    return (this->_topicRestricted);
}

void	Channel::setTopicRestricted(bool value)
{
    this->_topicRestricted = value;
}

bool	Channel::hasUserLimit(void) const
{
    return (this->_userLimit > 0);
}

size_t	Channel::getUserLimit(void)	const
{
    return (this->_userLimit);
}

void	Channel::setUserLimit(int limit)
{
    if (limit > 0)
        _userLimit = limit;
}

// === USER STATUS GETTERS ===

/**
 * @brief Validates network bindings determining specific role associations referencing internal map tracks.
 * Iterates internal client vector bounds attempting FD descriptor matches targeting active connection checks.
 * 
 * @param fd Target socket description determining connected network identities.
 * @return True when a sequential match binds within current map states. False mapping absent validation tracks.
 */
bool	Channel::isMember(int fd) const
{
    for (size_t index = 0; index < _members.size(); index++)
    {
        if (_members[index]->getFd() == fd)
            return (true);		
    }
    return (false);
}

bool	Channel::isOperator(int fd) const
{
    if (_operators.find(fd) != _operators.end())
        return (true);
    return (false);
}

bool	Channel::isInvited(int fd) const
{
    if (_inviteds.find(fd) != _inviteds.end())
        return (true);
    return (false);
}

size_t	Channel::getMembersCount(void) const		
{
    return (this->_members.size());
}

size_t	Channel::getOperatorsCount(void) const
{
    return (this->_operators.size());
}

size_t	Channel::getInvitedsCount(void) const
{
    return (this->_inviteds.size());
}

bool	Channel::hasNoMembers(void) const
{
    if (_members.empty())
        return (true);
    return (false);
}

/// === MEMBER MANAGEMENT ===

/**
 * @brief Registers mapped network tracking structures defining channel-specific user integrations.
 * 
 * Execution Flow:
 * 1. Checks bounds validating existing duplicate entries or null pointers mapping connection contexts.
 * 2. Confirms active capacity blocks testing member isolation; assigns default Operator privileges dynamically 
 *    if the channel being created maps an empty membership list.
 * 3. Incorporates reference targets into membership structures attaching new client instances.
 * 4. Cleans obsolete invite tracks if an explicitly targeted user successfully complete mapped associations.
 * 
 * @param newClient Target mapped pointer instance specifying incoming user connection details.
 * @return True when registration routines succeed without conflicts.
 */
bool	Channel::addMember(Client* newClient)
{
    int fd = newClient->getFd();

    if (!newClient || isMember(fd))
        return (false);	

    if (_members.empty())
        addOperator(fd);
    _members.push_back(newClient);	
    
    if (isInvited(fd))
        removeInvited(fd);		
    return (true);
}

/**
 * @brief Enforces client extraction purging mapping array references to a targeted socket identifier bounds.
 * 
 * Execution Steps:
 * 1. Iterates internal vectors determining sequence indexes holding identical targets for safe deletion bindings.
 * 2. Shifts structural memory cleanly erasing disconnected user entities.
 * 3. Assesses operator context for removed users. If the final active Administrator departs, safely triggers automatic 
 *    operator promotions to consecutive succeeding nodes preventing ownerless channel anomalies.
 * 
 * @param client Logical pointer specifying the unregistered mapped target handling disconnect contexts.
 */
void	Channel::removeMember(Client* client)
{
    std::vector<Client *>::iterator iterator = _members.begin();
    int	fd = client->getFd();

    if (!client)
        return ;
    for(; iterator != _members.end(); iterator++)
    {
        if ((*iterator)->getFd() == fd)
        {
            _members.erase(iterator);
            if (isOperator(fd))
            {
                removeOperator(fd);
                if (!_members.empty() & _operators.empty())
                    promoteFirstMember();
            }			
            break ;
        }
    }	
}

/**
 * @brief Assigns succession authority privileges tracking abandoned ownership handling default fallback instances.
 * 
 * @return Newly elevated Client tracking instance mapped with explicit operator flag properties.
 */
Client*	Channel::promoteFirstMember(void)
{
    Client * firstMember = _members[0];

    if (_members.empty())
        return (NULL);
    addOperator(firstMember->getFd());
    return (firstMember);
}

Client* Channel::findMemberByNick(const std::string &nickname)
{
    std::vector<Client *>::iterator	it = _members.begin();

    for(; it != _members.end(); it++)
    {
        if ((*it)->getNickname() == nickname)
            return (*it);			
    }
    return (NULL);
}

/// === OPERATOR MANAGEMENT ===	

void	Channel::addOperator(int fd)
{
    _operators.insert(fd);
}

void	Channel::removeOperator(int fd)
{
    _operators.erase(fd);
}

/// === INVITATION MANAGEMENT ===

void	Channel::addInvited(int fd)
{
    _inviteds.insert(fd);
}

void	Channel::removeInvited(int fd)
{
    _inviteds.erase(fd);
}

/// === UTILITIES ===

/**
 * @brief Constructs a sequential list mapping linked network alias identifiers separated by spaces.
 * Format generated (e.g. "@op1 @op2 user1 user2"). Evaluates identity map marking Operator accounts dynamically with '@'.
 * 
 * @return Concatenated continuous tracking explicit references mapping connected identifiers.
 */
std::string Channel::getMemberList(void)
{
    std::string membersList;
    std::vector<Client *>::iterator it = _members.begin();

    for(; it != _members.end(); it++)
    {
        if (isOperator((*it)->getFd()))
            membersList += "@";	

        membersList += (*it)->getNickname();
        if ((it + 1) != _members.end())
            membersList += " ";
    }
    return (membersList);
}

/**
 * @brief Compiles tracking metrics responding directly towards parameter-less MODE inquiry functions.
 * Assesses boolean matrix defining states [+i, +t, +k, +l] returning grouped representation components.
 * 
 * @return Explicit tracking signature combining matching modes prefixes using '+' structures.
 */
std::string Channel::getModeString(void) const
{
    std::string modesList;

    modesList += "+";
    if (_invitedOnly)
        modesList += "i";
    if (_topicRestricted)
        modesList += "t";
    if (hasPasswordChannel())
        modesList += "k";
    if (hasUserLimit())
        modesList += "l";
        
    if (modesList == "+")
        return ("");
    return (modesList);
}

/**
 * @brief Accumulates vectors identifying active mapped nodes expecting system interactions bypassing specific execution sources.
 * Generates tracking ID matrix pushing connection sequences exclusively ignoring target specific `exceptFd`.
 * 
 * @param exceptFd Isolated source map socket index circumventing targeted internal broadcasting cycles.
 * @return Constructed notification vector holding target indices mapped effectively.
 */
std::vector<int> Channel::getBroadcastFds(int exceptFd) const 
{
    std::vector<int> targets;

    for (size_t index = 0; index < _members.size(); index++) 
    {
        if (_members[index]->getFd() != exceptFd)
            targets.push_back(_members[index]->getFd());
    }
    return (targets);
}
