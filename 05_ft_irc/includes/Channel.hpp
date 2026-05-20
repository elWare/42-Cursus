/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:33:43 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 12:53:52 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

# include <string>
# include <vector>
# include <set>

# include "Client.hpp"

# define CHANNEL_ID					"[Channel] \t"
# define CONSTRUCTOR_MSG    		"Default Constructor: object created.\t"
# define COPY_CONSTRUCTOR_MSG		"Copy Constructor: object created.\t"
# define ASSIGNMENT_MSG				"Assignment operator: obj created.\t"
# define DESTRUCTOR_MSG	    		"Destructor: object destroyed.\t"
# define PARAM_CONSTRUCTOR_MSG		"Parametric Constructor: object created."

class Channel
{
	public:
		// === CONSTRUCTORS AND DESTRUCTOR ===
		Channel(void);
		~Channel(void);	
		Channel(const std::string &name);

		// === GETTERS + SETTERS ===
		const std::string&	getName(void)	const;

		const std::string&	getTopic(void)	const;
		void				setTopic (const std::string &newTopic);
		
		const std::string&	getPassword(void) 		const;
		bool				hasPasswordChannel(void) const;	
		void				setPasswordChannel (const std::string &newPassword);			

		// === CHANNEL MODES ===
		bool	isInviteOnly(void) 		const;
		void	setInvitedOnly(bool value);

		bool	isTopicRestricted(void) const;
		void	setTopicRestricted(bool value);

		bool	hasUserLimit(void) 		const;
		size_t	getUserLimit(void) 		const;
		void	setUserLimit(int limit);

		// === USER STATUS GETTERS ===		
		bool	isMember(int fd) 		const;	
		bool	isOperator(int fd) 		const;	
		bool	isInvited(int fd) 		const;
		size_t	getMembersCount(void)	const;		
		size_t	getOperatorsCount(void) const;		
		size_t	getInvitedsCount(void) 	const;
		bool	hasNoMembers(void)		const;		

		// === MEMBER MANAGEMENT ===
		bool	addMember(Client* newClient);
		void	removeMember(Client* client);
		Client*	promoteFirstMember(void);
		Client* findMemberByNick(const std::string &nickname);		

		// === OPERATOR MANAGEMENT ===	
		void	addOperator(int fd);
		void	removeOperator(int fd);		

		// === INVITATION MANAGEMENT ===
		void	addInvited(int fd);
		void	removeInvited(int fd);

		// === UTILITIES ===
		std::string getMemberList(void);

		std::string getModeString(void) const;		

		// === MESSAGE BROADCAST === 
		std::vector<int> getBroadcastFds(int exceptFd) const;

	private:
		std::string		_name;
		std::string		_topic;
		std::string		_passwordChannel;

		// === CHANNEL MODES ===					
		bool	_invitedOnly;
		bool	_topicRestricted;
		size_t	_userLimit;

		// === USER LIST ===
		std::vector<Client *>	_members;
		std::set<int>			_operators;
		std::set<int>			_inviteds;
};

#endif

/*
** CHANNEL CLASS - Represents an IRC Group Chat
** ===============================================================================
** A channel is a virtual meeting point allowing multi-user communication.
** It encapsulates group state, access control, and message distribution logic.
**
** CHANNEL ATTRIBUTES:
** -------------------
** - Name: Unique identifier starting with '#' or '&'.
** - Members: A registry of all connected clients currently in the channel.
** - Operators: Clients with elevated privileges (indicated by '@' prefix).
** - Topic: An optional string describing the channel's purpose.
** - Modes: Bitwise or boolean flags governing channel behavior and security.
**
** SUPPORTED CHANNEL MODES:
** ------------------------
** +i (Invite-Only):  Entry is restricted to users previously added to the 
** invitation list via the INVITE command.
** +t (Topic-Lock):   Restricts the ability to modify the channel topic exclusively 
** to users with Operator status.
** +k (Channel Key):  Implements password protection; requires the correct string 
** to be provided during the JOIN sequence.
** +o (Operator):     A toggle mode used to grant or revoke administrative 
** privileges to a specific member.
** +l (User Limit):   Sets a maximum occupancy threshold; prevents new joins 
** once the member count reaches the defined limit.
**
** USER HIERARCHY & PERMISSIONS:
** -----------------------------
** ┌────────────────┐
** │ OPERATOR (@)   │ → Privileges: KICK, INVITE, TOPIC (if +t), MODE changes.
** └───────┬────────┘
** │
** ┌───────▼────────┐
** │ MEMBER         │ → Privileges: PRIVMSG, NOTICE, VIEW TOPIC, PART.
** └────────────────┘
**
** PROTOCOL INHERITANCE:
** ---------------------
** - The channel creator (first client to JOIN a non-existent channel) 
** is automatically promoted to Operator status by the server.
** - Channels are dynamically destroyed when the last member departs.
*/