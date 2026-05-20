/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 11:12:27 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 11:44:30 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

# include <iostream>
# include <string>

# define SUCCESS	0
# define ERROR		1

# define CLIENT_ID					"[Client] \t"
# define CONSTRUCTOR_MSG    		"Default Constructor: object created.\t"
# define COPY_CONSTRUCTOR_MSG		"Copy Constructor: object created.\t"
# define ASSIGNMENT_MSG				"Assignment operator: obj created.\t"
# define DESTRUCTOR_MSG	    		"Destructor: object destroyed.\t"
# define PARAM_CONSTRUCTOR_MSG		"Parametric Constructor: object created."

# define SEND_SYSTEMCALL_ERROR		"Error: Sending data to the Client: "

class Client
{
	public:
		// === CONSTRUCTORS AND DESTRUCTOR ===
		Client(void);
		Client(int fd, const std::string& ip);
		~Client(void);				

		// === GETTERS ===
		int					getFd(void) 		const;
		const std::string&	getIp(void)			const;

		const std::string&	getNickname(void)	const;
		const std::string&	getUsername(void)	const;
		const std::string&	getRealname(void)	const;	

		const std::string&	getRecvBuffer(void) const;		

		// === STATE GETTERS ===
		bool	hasPassword(void) 	const;
		bool	hasNick(void)		const;
		bool	hasUser(void)		const;
		bool	isRegistered(void)	const;
		bool	isOperator(void)	const;
		
		// === SETTERS ===
		void	setNickname(const std::string &nickname);
		void	setUsername(const std::string &username);
		void	setRealname(const std::string &realname);

		void	setHasPassword(bool value);
		void	setHasNick(bool value);
		void	setHasUser(bool value);
		void	setOperator(bool value);		

		// === BUFFER HANDLING ===
		void		appendToBuffer(const std::string &data);
		void		clearBuffer(void);
		std::string	extractRawMessage(void);	
		bool		hasPendingOutputData(void) const;	

		// === MESSAGE SENDING ===
		void				sendBuffer(const std::string &message);
		const std::string&	getSendBuffer(void) const;
		void 				eraseSentBytes(size_t sentBytes);

		// === UTILITIES ===
		std::string	getPrefix(void) const;
		
	private:		
		// --- Protocolo TCP + socket ---
		int 			_fd;
		std::string		_ip;
		
		// --- Buffer reception TCP ---
		
		std::string 	_inputBuffer;
		std::string		_outputBuffer;

		// --- IRC Identity ---
		std::string		_nickname;
		std::string		_username;
		std::string		_realname;

		// --- State ---
		bool			_hasPassword;
		bool			_hasNick;
		bool			_hasUser;
		bool			_isOperator;
};

#endif

/*
** CLIENT CLASS - Represents an Individual User Session
** ===============================================================================
** A client is a unique connection to the server, defined by its network 
** identity and its current state within the IRC protocol handshake.
**
** CLIENT ATTRIBUTES:
** ------------------
** - File Descriptor (FD): The unique socket identifier for network I/O.
** - Nickname: The visual identity used to address the user in channels.
** - Username: The account identifier provided during the USER command.
** - Realname: An optional descriptive string for the user's profile.
** - IP Address: The originating host address used for prefix construction.
**
** REGISTRATION HANDSHAKE STATE:
** -----------------------------
** To become an active member, a client must satisfy three flags:
** 1. HasPassword: Confirms the correct server password was provided (PASS).
** 2. HasNick:     Confirms a unique nickname has been assigned (NICK).
** 3. HasUser:     Confirms session identity has been established (USER).
**
** VALIDATION & SECURITY:
** ----------------------
** - Prefix: A synthesized string (:nick!user@host) used as the global 
** identifier for all relayed messages.
** - Registration Gate: Restricted commands (JOIN, PRIVMSG) are blocked until 
** the client state is set to isRegistered() = true.
** - Buffering: Each client maintains its own I/O buffers to handle 
** asynchronous message processing.
**
** LIFECYCLE MANAGEMENT:
** ---------------------
** ┌──────────────┐      ┌──────────────┐      ┌──────────────┐
** │  CONNECTED   │  →   │ REGISTERING  │  →   │  REGISTERED  │
** │ (Raw Socket) │      │ (Handshaking)│      │ (Active User)│
** └──────────────┘      └──────────────┘      └──────────────┘
**
** Clients are automatically removed from the global state upon socket 
** disconnection or after a QUIT command execution.
*/