/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:19:12 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/15 13:43:18 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Server.hpp"
# include "../../includes/CommandExecutor.hpp"

// === CONSTRUCTORS AND DESTRUCTOR ===

/**
 * @brief Default constructor for Server.
 * Initializes socket and port defaults. CLEANS memory blocks for server address to avoid garbage data.
 */
Server::Server(void)
    :	_port(-1), _serverFd(-1), _ip("")
{
    std::memset(&_servAddress, 0, sizeof(_servAddress));
}

/**
 * @brief Destructor for Server.
 * Safely shuts down the server.
 * 1. Sends a shutdown system message to all connected clients.
 * 2. Closes all open active file descriptors (sockets) within the pollfds array.
 */
Server::~Server(void)
{
    std::string shutdownMsg = SHUTDOWN_MSG;
    
    for (size_t index = 0; index < _pollfds.size(); index++)
        if (_pollfds[index].fd != -1)
        {
            if (_pollfds[index].fd != _serverFd)				
                send(_pollfds[index].fd, shutdownMsg.c_str(), shutdownMsg.length(), 0);
            close(_pollfds[index].fd);
        }
}

/**
 * @brief Parameterized constructor for Server.
 * @param port The port number the server will listen on.
 * @param executor Reference to the CommandExecutor handling the IRC logic routing.
 */
Server::Server(int port, CommandExecutor &executor)
    :	_executor(&executor), _port(port), _serverFd(-1), _ip("")
{ }

// === MAIN ===

/**
 * @brief Initializes the network socket setup for the server.
 * 
 * Execution Steps:
 * 1. Creates the TCP/IPv4 Server Socket via system call.
 * 2. Configures socket options (SO_REUSEADDR) to prevent TIME_WAIT locks and allow immediate restart.
 * 3. Sets the socket behavior to Non-Blocking (O_NONBLOCK) by altering file control flags via fcntl.
 * 4. Configures the internet socket address layout (IP mapping and port conversions via htons).
 * 5. Binds the configured file descriptor to the assigned port and wildcard IP (INADDR_ANY).
 * 6. Sets the initialized socket to passive LISTEN state with max queue capacity (SOMAXCONN).
 * 7. Adds the primary server socket to the poll descriptor array to monitor for incoming POLLIN events.
 * 
 * @return SUCCESS (0) if initialization is fully completed, ERROR (-1) on any system call failure.
 */
int Server::initServer(void)
{
    _serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverFd < 0)
    {
        std::cerr << SOCKET_SYSTEMCALL_ERROR << std::endl;
        return (ERROR);
    }

    int option = ENABLE_SOCK_OPT;						
    int setsockopt_status = setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (setsockopt_status < 0)
    {
        close(_serverFd);
        std::cerr << SETSOCKOPT_SYSTEMCALL_ERROR << std::endl;
        return (ERROR);
    }

    int flags = fcntl(_serverFd, F_GETFL, 0);				
    fcntl(_serverFd, F_SETFL, flags | O_NONBLOCK);			

    _servAddress.sin_family			= AF_INET;		
    _servAddress.sin_port			= htons(_port);	
    _servAddress.sin_addr.s_addr 	= INADDR_ANY;	

    char ipString[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &_servAddress.sin_addr, ipString, INET_ADDRSTRLEN);	
    this->_ip = ipString;

    int bind_status = bind(_serverFd, (sockaddr*) &_servAddress, sizeof(_servAddress));
    if (bind_status < 0)
    {
        close(_serverFd);
        std::cerr << BIND_SYSTEMCALL_ERROR << std::endl;
        return (ERROR);
    }	

    int	listen_status = listen(_serverFd, SOMAXCONN); 
    if (listen_status < 0)
    {
        close(_serverFd);
        std::cerr << LISTEN_SYSTEMCALL_ERROR << std::endl;
        return (ERROR);
    }

    _serverPoll.fd 		= _serverFd;
    _serverPoll.events	= POLLIN;		
    _serverPoll.revents = 0;		
    _pollfds.push_back(_serverPoll);	

    displayWelcome();    
    return (SUCCESS);
}

/**
 * @brief Core Event Loop for processing multiplexed I/O connections.
 * 
 * Execution flow using poll() API:
 * 1. Synchronize the desired event masks for active sockets (setting POLLIN and checking for POLLOUT).
 * 2. Invoke poll() and wait for synchronous network activity without wasting CPU cycles.
 * 3. Inspect each socket in the descriptor list for active event flags:
 *    - DISCONNECTION (POLLHUP/POLLERR/POLLNVAL): Abort connection immediately and cleanup.
 *    - READ (POLLIN):
 *        * If the target is the Main Server Socket, trigger acceptNewClient() for incoming connections.
 *        * If the target is a Client Socket, trigger receiveClient() to pipe stream data into local buffers.
 *    - WRITE (POLLOUT): 
 *        * Extract pending outbound data from the target client.
 *        * Push via send() and track system limits (EAGAIN/EWOULDBLOCK safe).
 *        * Disable POLLOUT dynamically if no further data is enqueued.
 * 
 * @return SUCCESS (0) on expected graceful exit, or ERROR (-1) on fatal interrupt.
 */
int Server::run(void)
{
    while (glb_keeprunning)
    {
        int activeSockets = poll(&_pollfds[0], _pollfds.size(), POLL_INFINITE_TIMEOUT);
        if (activeSockets < 0)
        {
            if (errno == EINTR)
                continue;
            std::cerr << POLL_SYSTEMCALL_ERROR << std::endl;
            return (ERROR);
        }
        
        for (size_t index = 0; index < _pollfds.size(); index++)
        {
            if (_pollfds[index].revents & (POLLHUP | POLLERR | POLLNVAL))
            {
                if (_pollfds[index].fd != _serverFd)
                {
                    std::cerr << DISCONNECTION_CLIENT_ERROR << _pollfds[index].fd << std::endl;
                    disconnectClient(index);
                    index--;		
                }
                continue ;
            }

            if (_pollfds[index].revents & POLLIN)	
            {
                if (_pollfds[index].fd == _serverFd)
                    acceptNewClient();
                else	
                {
                    size_t sizeRecv = _pollfds.size();
                    readClientData(index);
                    if (_pollfds.size() < sizeRecv)
                        index--;
                }
            }	

            if (_pollfds[index].revents & POLLOUT)
            {
                size_t sizeBefore = _pollfds.size();

				sendClientData(index);				
				if (_pollfds.size() < sizeBefore)
					index--;
            }
        }
    }
    return (SUCCESS);
}

// === GETTERS ===

int	Server::getServerFd(void)
{
    return (this->_serverFd);
}

std::vector<pollfd>	Server::getPollfds(void)
{
    return (this->_pollfds);
}

// === NETWORK OPERATIONS ===

/**
 * @brief Handles establishing newly requested client connections.
 * 
 * Execution Steps:
 * 1. Derives a new distinct file descriptor for the connecting client interacting directly with accept().
 * 2. Assigns standard non-blocking (O_NONBLOCK) properties via fcntl flags to the newly formed socket.
 * 3. Converts binary IP address headers to human-readable String types via inet_ntop.
 * 4. Pushes the newly generated client descriptor onto the primary IO pollfd array, tracked for POLLIN.
 * 5. Connects logic model instances inside CommandExecutor referencing this newly created client ID.
 * 
 * @return SUCCESS on standard completion, or ERROR on accept() system call failure.
 */
int Server::acceptNewClient(void)
{
    sockaddr_in	clientAddress;
    socklen_t	addressLength = sizeof(clientAddress);

    int newClient_fd = accept(_serverFd, (sockaddr *) &clientAddress, &addressLength);
    if (newClient_fd < 0)
    {
        std::cerr << CONNECTION_SYSTEMCALL_ERROR << std::endl;
        return (ERROR);
    }

    int flags = fcntl(_serverFd, F_GETFL, 0);				
    fcntl(newClient_fd, F_SETFL, flags | O_NONBLOCK);		

    char ipString[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddress.sin_addr, ipString, INET_ADDRSTRLEN);

    pollfd	clientPollFd;
    clientPollFd.fd 		= newClient_fd;
    clientPollFd.events		= POLLIN;
    clientPollFd.revents	= 0;
    
    _pollfds.push_back(clientPollFd);
    _executor->onClientConnect(newClient_fd, std::string(ipString));	

    return (SUCCESS);
}

/**
 * @brief Reads network bytes directly into the server state instance buffers.
 * 
 * Execution Steps:
 * 1. Triggered on active poll descriptor event POLLIN for client instances.
 * 2. Fetches sequential bytes from the system recv() stream matching the 1024 char temporary block.
 * 3. Checks for grace disconnections denoted by a returned stream length of 0.
 * 4. Appends incoming chunks to the Client Model's private sequential buffer cache.
 * 5. Passes parsing execution logic onto processClientBuffer() via reference context.
 * 
 * @param index The positional index targeting the actively flagged pollfd internal struct arrays.
 * @return SUCCESS on resolution (including block limits/EOF) or ERROR resolving system stream failures.
 */
int Server::readClientData(int index)
{
    int 	fd = _pollfds[index].fd;    
    char	socketBuffer[RECV_BUFFER_SIZE];
    int 	bytes = recv(fd, socketBuffer, sizeof(socketBuffer) - 1, 0);	

    if (bytes == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return (SUCCESS);
        else
        {
            std::cerr << RECEIVE_BYTES_ERROR << std::endl;
            return (ERROR);
        }
    }
    else if (bytes == 0)				
    {
        disconnectClient(index);
        return (SUCCESS);
    }
    socketBuffer[bytes] = '\0';    
    Client *client = _executor->getClient(fd);	
    client->appendToBuffer(socketBuffer);		
   if (!client)
    {
        disconnectClient(index);
        return (SUCCESS);
    } 
    routeClientMessages(*client);
    return (SUCCESS);
}

int Server::sendClientData(int index)
{
    int 	fdClient 	= _pollfds[index].fd;
    Client* client 		= _executor->getClient(fdClient);

    if (client && client->hasPendingOutputData())
    {
        const std::string &dataToSend = client->getSendBuffer();
        ssize_t sentBytes = ::send(fdClient, dataToSend.c_str(), dataToSend.size(), MSG_DONTWAIT);
        
        if (sentBytes < 0)
        {
            std::cerr << POLLOUT_SENDBYTES_ERROR << fdClient << std::endl;
            this->disconnectClient(index); 
            return (ERROR);
        }
        else if (sentBytes > 0)
            client->eraseSentBytes(sentBytes);

        if (!client->hasPendingOutputData())
            _pollfds[index].events &= ~POLLOUT;
    }
    else
		_pollfds[index].events &= ~POLLOUT;
	return (SUCCESS);
}

/**
 * @brief Severs all socket linkages from a target client.
 * 
 * Closes network level descriptors from the Operating System, purges vector instances targeting 
 * poll interactions, and notifies the external logical router implementation to deregister context blocks.
 * 
 * @param index Pointer iterating descriptor targeting mapped file indexes bounds.
 */
void Server::disconnectClient(int index)
{
    int fd = _pollfds[index].fd;

    close(fd);									
    _pollfds.erase(_pollfds.begin() + index);
    _executor->onClientDisconnect(fd);	
}

// === INPUT BUFFER TCP LAYER ===

/**
 * @brief Handles incoming streams processing extracted buffer bytes into modeled structures parsing IRC properties.
 * 
 * Execution Flow:
 * 1. Checks bounds for continuous message strings and divides trailing strings matching standardized breaks (\r\n).
 * 2. Secures string size compliance via strict bounding checks on acceptable lengths (512 max per IRC standard).
 * 3. Evaluates String block syntax translating into structured Smart Objects (IRCMessage DTO).
 * 4. Pushes DTO blocks onto the execution router tracking requested contexts.
 * 5. Maps return block contents iterating all resulting output vectors (Responses), redirecting data buffers
 *    matching targeted client FDs whilst turning on specific descriptor flags matching dynamic write requests (POLLOUT).
 * 
 * @param client Logical context defining incoming connection requesting processing logic.
 */
void Server::routeClientMessages(Client &client)
{
    std::string	rawMessage;
	int	clientFd = client.getFd();

    while (_executor->getClient(clientFd) && (rawMessage = client.extractRawMessage()) != "")
    {		
        if (rawMessage.size() > (IRC_MAX_MSG_SIZE - CRLF_LENGTH))	
        {
            std::cerr << MAX_SIZE_BUFFER_ERROR << std::endl;
            continue ;
        }

        IRCMessage msg(rawMessage);
        msg = Parser::parse(rawMessage); 
        if (msg.getCommand().empty()) 
            continue ; 		
        
        _executor->execute(client, msg);	
		if (_executor->getClient(clientFd) == NULL)
            return ;
				
        const std::vector<Response> &responses = msg.getResponses();

        for (size_t pollIndex = 0; pollIndex < responses.size(); pollIndex++)
        {
            const std::string		&textToSend		= responses[pollIndex].text;
            const std::vector<int>	&destinationFds = responses[pollIndex].targetFds;

            for (size_t targetIndex = 0; targetIndex < destinationFds.size(); targetIndex++)
            {
                int targetFd = destinationFds[targetIndex];

                Client* destClient = _executor->getClient(targetFd);
                if (!destClient)
                    return ;       

                destClient->sendBuffer(textToSend); 
				updatePollOutEvent(targetFd);				
            }
        }	
		if (client.hasPendingOutputData())
			updatePollOutEvent(clientFd);	
    }	
}	

// === UTILITIES ===

/**
 * @brief Reactively enables the POLLOUT event flag for a specific target client.
 * 
 * Execution Steps:
 * 1. Invoked strictly on-demand by the network layer precisely when a response buffer is populated.
 * 2. Iterates the poll descriptor array to locate the struct matching the provided File Descriptor.
 * 3. Uses a bitwise OR (|=) operator to safely inject the POLLOUT state without overwriting the existing POLLIN state.
 * 
 * @param fd The native File Descriptor of the specific client that needs its output flow unblocked.
 */
void Server::updatePollOutEvent(int fd) 
{
	for (size_t index = 1; index < _pollfds.size(); index++) 
	{
		if (_pollfds[index].fd == fd)
		{
			_pollfds[index].events |= POLLOUT;
			break ; 
		}
	}
}

/**
 * @brief Renders CLI UI presentation context showing startup banner and configured mapping metrics.
 */
void Server::displayWelcome(void)
{
    const std::string RESET = "\033[0m";
    const std::string BOLD  = "\033[1m";
    const std::string CYAN  = "\033[36m";
    const std::string RED   = "\033[31m";

    std::string frames[] = {"[=     ]", "[==    ]", "[===   ]", "[====  ]", "[===== ]", "[======]"};    
    std::cout << BOLD << CYAN << "Starting IRC server... " << RESET << std::flush;
    
    for (int i = 0; i < 3; ++i) { 
        for (int j = 0; j < 6; ++j) {
            std::cout << "\r" << BOLD << CYAN << "Starting IRC server " << frames[j] << RESET << std::flush;
            usleep(150000);
        }
    }
    std::cout << "\r\n" << BOLD << "\033[32mServer Ready!          " << RESET << std::endl;

    std::cout << "\n\n";
    std::cout << "\033[94m  ██╗██████╗  ██████╗███████╗███████╗██████╗ ██╗   ██╗"	<< std::endl;
    std::cout << "\033[94m  ██║██╔══██╗██╔════╝██╔════╝██╔════╝██╔══██╗██║   ██║"	<< std::endl;
    std::cout << "\033[34m  ██║██████╔╝██║      ███████╗█████╗  ██████╔╝██║   ██║"	<< std::endl;
    std::cout << "\033[34m  ██║██╔══██╗██║      ╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝"	<< std::endl;
    std::cout << "\033[36m  ██║██║  ██║╚██████╗███████║███████╗██║  ██║ ╚████╔╝ "	<< std::endl;
    std::cout << "\033[36m  ╚═╝╚═╝  ╚═╝ ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  " << RESET << std::endl;
    
    std::cout << std::endl << BOLD << "\t\t IRC Server [ " << SERVER_NAME << " ]"				 << RESET << std::endl;
    std::cout << std::endl << BOLD << CYAN  << "IRC server started on port <" << _port << ">..." << RESET << std::endl;
    std::cout << BOLD << CYAN << "Ip IRC <" << _ip   << ">..." 									 << RESET << std::endl;
    std::cout << BOLD << CYAN << "Waiting for connections ..." 									 << RESET << std::endl;
}
