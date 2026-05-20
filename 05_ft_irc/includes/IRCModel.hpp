/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCModel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:28:16 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 11:48:31 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSTATE_HPP
#define IRCSTATE_HPP

# include <iostream>
# include <string>
# include <map>

# include "./Client.hpp"
# include "./Channel.hpp"
# include "./Bot.hpp"

# define IRC_MODEL_ID					"[IrcModel] \t"

// SAVES THE SERVER'S INTERNAL STATE
// Stores and manages Client and Channel instances through global state.
// He knows nothing about sockets or protocols, only about data. His responsibility is to ensure that maps or vectors are clean without applying chat command logic.
class IRCModel
{
	public:
		// === CONSTRUCTORS AND DESTRUCTOR ===
		IRCModel(void);
		~IRCModel(void);	

		// === MAIN CONST PARAM ===	
		IRCModel(const std::string &password);

		// === GETTERS ===
		std::map<int, Client>& 			getClientsMap(void);
		std::map<std::string, Channel>	getChannelsMap(void);

		// === PASSWORD ===
		const std::string& 	getPassword(void) const;
		void				setPassword(const std::string& newPassword);

		// === CLIENT MANAGEMENT ===
		Client*	addClient(int fd, const std::string &ip);
		Client*	getClient(int fd);
		Client* getClientbyNick(const std::string &nickname);
		void	unregisterClient(int fd); 			

		// === CHANNEL MANAGEMENT ===	
		Channel*	getOrCreateChannel(const std::string &name);
		Channel*	getChannel(const std::string &name);	

	private:
		// === STATE ATTRIBUTES ===		
		std::string		_password;

		/// ALMACEN FDS CLIENTES + CHANNELS
		std::map<int, Client> 			_clients;	
		std::map<std::string, Channel> 	_channels;	
		Client							_bot; 		
		
		// === INTERNAL METHODS ===	
		void	removeClientFromAllChannels(int fd);
};	

#endif