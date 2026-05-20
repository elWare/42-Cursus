/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCModel.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:28:23 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 11:48:31 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/IRCModel.hpp"

// === CONSTRUCTORS AND DESTRUCTOR ===

/**
 * @brief Default constructor for IRCModel.
 * Initializes the default system password as empty and sets up the internal bot instance.
 */
IRCModel::IRCModel(void)
    : _password("")
{
    initBot(_bot);
}

/**
 * @brief Destructor for IRCModel.
 * Safely handles the memory lifecycle for active connections.
 * Automatically clears the map of Clients and Channels, which invokes their respective ~Client() and ~Channel() destructors.
 */
IRCModel::~IRCModel(void)
{	
    _channels.clear();
    _clients.clear();
}

// === MAIN CONST PARAM ===

/**
 * @brief Parameterized constructor for IRCModel.
 * Sets the system wide password required for clients to access the IRC server.
 * 
 * @param password The secret key string required for initial network connections.
 */
IRCModel::IRCModel(const std::string &password)	
    :	_password(password)
{
    initBot(_bot);
}

// === GETTERS ===

std::map<int, Client>& IRCModel::getClientsMap(void)
{
    return (this->_clients);
}

std::map<std::string, Channel>	IRCModel::getChannelsMap(void)
{
    return (this->_channels);
}

// === PASSWORD ===

const std::string& 	IRCModel::getPassword(void) const
{
    return (this->_password);
}

void	IRCModel::setPassword(const std::string& newPassword)
{
    this->_password = newPassword;
}

// === CLIENT MANAGEMENT ===

/**
 * @brief Registers a newly connected client into the internal model.
 * Instantiates the client with its file descriptor and mapped IP, then stores it.
 * 
 * @param fd Target socket descriptor associated with the client.
 * @param ipString Parsed textual representation of the target IPv4 address.
 * @return A dynamically referenced pointer mapping to the newly stored Client block.
 */
Client*	IRCModel::addClient(int fd, const std::string &ipString)
{
    Client newClient (fd, ipString);

    _clients[fd] = newClient;	
    return (&_clients[fd]);
}

/**
 * @brief Retrieves a Client instance based on its socket file descriptor.
 * 
 * @param fd Target numeric socket descriptor.
 * @return Extracted instance pointer, or NULL if the client no longer exists.
 */
Client*	IRCModel::getClient(int fd)
{
    std::map<int, Client>::iterator it = _clients.find(fd);
    
    if (it != _clients.end())
        return (&it->second);
    return (NULL);
}

/**
 * @brief Searches for a Client across the mapped structures based strictly on its registered Nickname.
 * 
 * @param nickname Target client identification string.
 * @return Extracted instance pointer traversing iterating matches, or NULL if undiscovered.
 */
Client*	IRCModel::getClientbyNick(const std::string &nickname)
{
    std::map<int, Client>::iterator	it = _clients.begin();

    for (it = _clients.begin(); it != _clients.end(); it++)
    {
        Client &client = it->second;
        if (client.getNickname() == nickname)
            return (&client);
    }
    return (NULL);
}

/**
 * @brief Handles structural severing of a specified client from the main model map.
 * Enforces atomic cleanup by removing the user bounds spanning all interconnected channels 
 * prior to fully erasing the socket map record.
 * 
 * @param fd Network socket descriptor designated for removal.
 */
void	IRCModel::unregisterClient(int fd)
{	
    removeClientFromAllChannels(fd);	
    _clients.erase(fd);					
}

// === CHANNEL MANAGEMENT ===

/**
 * @brief Acquires an ongoing channel or initializes a new channel structure.
 * Validates channel existence by name. If unmapped, inserts a newly formed channel node block to the tracking map.
 * 
 * @param name Formatted IRC channel name mapping target.
 * @return A dynamically referenced pointer to the Channel instance node.
 */
Channel*	IRCModel::getOrCreateChannel(const std::string &name)
{
    Channel	*existingChannel = getChannel(name);
    if (existingChannel)
        return (existingChannel);

    Channel newChannel(name);	
    _channels[name] = newChannel;		
    return (&_channels[name]);
}

/**
 * @brief Locates an actively tracked channel matching a string key.
 * 
 * @param name Assumed target name of the requested Channel.
 * @return Identified valid Channel instance block, or NULL mapping fails.
 */
Channel*	IRCModel::getChannel(const std::string &name)
{
    std::map<std::string, Channel>::iterator it = _channels.find(name);

    if (it != _channels.end())
        return (&(it->second));
    return (NULL);
}

// === PRIVATE INTERNAL METHODS ===

/**
 * @brief Helper routine ensuring a targeted user is cleanly evicted from all existing channels.
 * 
 * Execution Steps:
 * 1. Checks validation mapping context fetching targeted physical Client IDs.
 * 2. Iterates tracking vectors scanning channels wherein the specific matching socket ID belongs as an active member.
 * 3. Instructs identified internal active mappings removing mapped users tracking auto operator promotions.
 * 4. Pushes newly vacated tracking blocks onto designated deletion vectors cleaning up server memory loads erasing channels bereft of members.
 * 
 * @param fd Target mapping descriptor defining the client undergoing un-registration.
 */
void	IRCModel::removeClientFromAllChannels(int fd)
{
    std::vector<std::string> emptyChannels;
    std::map<std::string, Channel>::iterator it = _channels.begin();
    
    Client *client = getClient(fd);
    if (!client)
        return ;

    for (; it != _channels.end(); it++)
    {
        Channel &channel = it->second;
        
        if (channel.isMember(fd))
        {
            channel.removeMember(client);

            if (channel.hasNoMembers())
                emptyChannels.push_back(it->first);
        }
    }
    
    for (size_t index = 0; index < emptyChannels.size(); index++)
        _channels.erase(emptyChannels[index]);		
}

