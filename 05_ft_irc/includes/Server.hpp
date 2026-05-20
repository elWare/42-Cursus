/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 20:36:39 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 16:43:26 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# include <iostream>	
# include <string>	
# include <cstring>		
# include <unistd.h>	

# include <vector>		
# include <map>			

# include <fcntl.h>		
# include <poll.h>		
# include <arpa/inet.h>

# include "./Signal.hpp"
# include "./Parser.hpp"
# include "./IRCMessage.hpp"

# define SERVER_ID					"[Server] \t"
# define CONSTRUCTOR_MSG    		"Default Constructor: object created.\t"
# define COPY_CONSTRUCTOR_MSG		"Copy Constructor: object created.\t"
# define ASSIGNMENT_MSG				"Assignment operator: obj created.\t"
# define DESTRUCTOR_MSG	    		"Destructor: object destroyed.\t"
# define PARAM_CONSTRUCTOR_MSG		"Parametric Constructor: object created."

# define SUCCESS	0
# define ERROR		1
# define FAILURE	-1

# define IRC_MAX_MSG_SIZE			512
# define RECV_BUFFER_SIZE 			1024

# define ENABLE_SOCK_OPT 			1
# define POLL_INFINITE_TIMEOUT 		-1
# define CRLF_LENGTH				2

# define NUMBER_ARGS_ERROR				"Error: Wrong number of arguments."
# define CONVERSION_ERROR				"Error: Conversion to number."
# define OUTRANGE_PORTS_ERROR			"Error: Out of range. Port limit between 1 and 65535."
# define PORTS_RANGE_RECOMMENDED		"It is recommended to use 'registered ports' [1024 - 49151] for application servers."

# define SOCKET_SYSTEMCALL_ERROR		"Error: creating socket failed."
# define SETSOCKOPT_SYSTEMCALL_ERROR	"Error: Setsockopt failed."
# define BIND_SYSTEMCALL_ERROR			"Error: Bind() failed. Port busy."
# define LISTEN_SYSTEMCALL_ERROR		"Error: Listen() failed."
# define POLL_SYSTEMCALL_ERROR			"Error: Error activity in poll()."
# define DISCONNECTION_CLIENT_ERROR		"Error: Sudden disconnection / Error detected in fd "
# define CONNECTION_SYSTEMCALL_ERROR 	"Error: Error accepting client connection."
# define SERVER_LOOP_ERROR				"Error: Run Server."
# define MAX_SIZE_BUFFER_ERROR			"Error: Command ignored: exceeds 512 bytes."	
# define RECEIVE_BYTES_ERROR			"Error: receiveClient()."
# define POLLOUT_SENDBYTES_ERROR		"Critical error in send() for FD "

# define SHUTDOWN_MSG					"ERROR: Server shutting down...\r\n"
# define SERVER_NAME					"WALL-E"

class CommandExecutor;		
class Client;              

// TCP CLASS SERVER
// Responsible for I/O multiplexing (poll), accepting TCP connections, reading sockets, and sending responses back. 
// Functions as a pure network layer.
class Server
{
	public:
		// === CONSTRUCTORS AND DESTRUCTOR ===	
		Server(int port, CommandExecutor &executor);
		~Server(void);			

		//  === MAIN ===
		int initServer(void);
		int	run(void);			

		// === GETTERS ===
		int					getServerFd(void);
		std::vector<pollfd>	getPollfds(void);	

	private:
		Server(void);

		// === IRC COMANDS EXECUTOR ===
		CommandExecutor	*_executor;

		int 		_port;
		int			_serverFd;
		sockaddr_in _servAddress;
		std::string	_ip; 

		// === FDS WAREHOUSE CUSTOMERS ===
		pollfd					_serverPoll;
		std::vector<pollfd> 	_pollfds;		

		// === NETWORK OPERATIONS ===
		int 	acceptNewClient(void);
		int		readClientData(int index);
		int		sendClientData(int index);
		void 	disconnectClient(int index);

		void	routeClientMessages(Client &client);

		// === UTILITIES ===
		void	updatePollOutEvent(int fd);
		void 	displayWelcome(void);			
	};

#endif

/*
** ==============================================================================
** TCP CLASS SERVER
** ================================================================================
**
** Steps to create a TCP socket server:
**
** 1. socket() - Creates the socket file descriptor
** 2. bind() - Binds the socket to a specific port
** 3. listen() - Marks the socket as "passive" (accepts connections)
** 4. accept() - Accepts connections Incoming Connections (made in the main loop)

** ** Why O_NONBLOCK?

** In blocking mode, recv() and accept() would pause the program until the data arrived.

** With O_NONBLOCK + poll(), we can monitor multiple clients simultaneously without threads or blocking.
*/