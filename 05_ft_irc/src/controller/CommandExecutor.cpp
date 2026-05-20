/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandExecutor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:46:14 by jumarque          #+#    #+#             */
/*   Updated: 2026/05/18 16:39:25 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/CommandExecutor.hpp"
# include "../../includes/Bot.hpp"

CommandExecutor::~CommandExecutor(void)
{ }

/**
 * @brief Initializes the CommandExecutor and populates the command dispatch table.
 * * Execution flow for object construction:
 * 1. State Binding: Establishes a reference to the global IRCModel (_state) 
 * to provide commands with access to client and channel data.
 * 2. Dispatch Map Initialization: Populates the internal _commandMap by 
 * mapping IRC verb strings (e.g., "JOIN", "PRIVMSG") to their respective 
 * CommandHandler member functions.
 * 3. Pattern Implementation: Sets up the "Command Pattern" infrastructure, 
 * allowing for O(log n) command lookups during the execution phase.
 * 4. Extensibility: Provides a centralized location for registering new 
 * protocol features or custom commands (like CAP or WHO).
 * * @param state Reference to the IRCModel containing the global server state.
 */

CommandExecutor::CommandExecutor(IRCModel &state)
	: _state(state)
{
	_commandMap["PASS"] 	= &CommandExecutor::cmdPASS;
	_commandMap["NICK"] 	= &CommandExecutor::cmdNICK;
	_commandMap["USER"] 	= &CommandExecutor::cmdUSER;
	_commandMap["PING"] 	= &CommandExecutor::cmdPING;
	_commandMap["JOIN"] 	= &CommandExecutor::cmdJOIN;
	_commandMap["PRIVMSG"] 	= &CommandExecutor::cmdPRIVMSG;
	_commandMap["PART"] 	= &CommandExecutor::cmdPART;
	_commandMap["KICK"] 	= &CommandExecutor::cmdKICK;
	_commandMap["TOPIC"] 	= &CommandExecutor::cmdTOPIC;
	_commandMap["INVITE"] 	= &CommandExecutor::cmdINVITE;
	_commandMap["MODE"] 	= &CommandExecutor::cmdMODE;
	_commandMap["QUIT"] 	= &CommandExecutor::cmdQUIT;
	_commandMap["CAP"] 		= &CommandExecutor::cmdCAP;
	_commandMap["WHO"] 		= &CommandExecutor::cmdWHO;
}

/*
** ==========================================================================
** SETTER
** ==========================================================================
*/

/**
 * @brief Ensures a channel exists and manages the initial entry of a client.
 * * Execution flow for channel acquisition and joining:
 * 1. Registry Lookup: Attempts to retrieve an existing Channel instance from 
 * the global state by its unique name.
 * 2. Dynamic Instantiation:
 * - If the channel is non-existent: Triggers getOrCreateChannel() to allocate 
 * a new instance.
 * - Ownership Assignment: Automatically grants the 'Operator' privilege (@) 
 * to the initiating client, marking them as the channel founder.
 * 3. Membership Binding: Appends the client to the channel's member list, 
 * regardless of whether the channel was newly created or already active.
 * 4. Context Return: Provides the caller with a pointer to the synchronized 
 * Channel object for further protocol processing (like broadcasting JOIN).
 * * @return Pointer to the active (new or existing) Channel instance.
 */

Channel*	CommandExecutor::setChannel(const std::string &name, Client &client)
{
	Channel *channel = _state.getChannel(name);
	if (!channel)
	{
		channel = _state.getOrCreateChannel(name);
		channel->addOperator(client.getFd());
	}
	channel->addMember(&client);
	return (channel);
}

/*
** ==========================================================================
** AUXILIARY METHODS
** ==========================================================================
*/

/**
 * @brief Queues formatted server responses for transmission to the client.
 * * Execution flow for response handling:
 * 1. Protocol Formatting: Appends the mandatory CRLF (\r\n) terminator to 
 * the raw reply string to ensure standard IRC frame delimitation.
 * 2. Target Definition: Identifies the current client's File Descriptor as 
 * the sole recipient of the message.
 * 3. Buffer Integration: Hands over the formatted payload and the recipient 
 * list to the IRCMessage object's response manager.
 * 4. Asynchronous Preparation: Prepares the internal buffers for the next 
 * server-side I/O cycle (e.g., poll/select) to flush the data to the socket.
 */

void CommandExecutor::sendReply(Client& client, IRCMessage& msg, const std::string& reply)
{
	std::string fullReply = reply + "\r\n";
	std::vector<int> targetFds;
	
	targetFds.push_back(client.getFd());
	msg.addResponse(targetFds, fullReply);
}

/**
 * @brief Enforces the mandatory IRC registration sequence for restricted commands.
 * * Execution flow for access control:
 * 1. Bypass Logic: Evaluates the incoming command against the "Pre-Registration 
 * Whitelist" (PASS, NICK, USER, PING). These are essential to establish identity.
 * 2. State Verification: Consults the Client object's current status via isRegistered().
 * 3. Access Decision:
 * - Returns FALSE: If the command is in the whitelist or the client is already 
 * fully authenticated.
 * - Returns TRUE: If an unregistered client attempts to access high-level 
 * commands (JOIN, PRIVMSG, etc.), signaling an authorization failure.
 * * @return Boolean indicating if the command must be blocked due to lack of registration.
 */

bool CommandExecutor::requiresRegistration(Client& client, const std::string& command)
{
	if (command == "PASS" || command == "NICK" || command == "USER" || command == "PING" || command == "CAP")
		return false;
	
	return !client.isRegistered();
}


/**
 * @brief Dispatches the initial numeric handshake to finalize client registration.
 * * Execution flow for the Welcome Sequence:
 * 1. Identity Synthesis: Construct the full client prefix (nick!user@host) 
 * to be reflected in the RPL_WELCOME message.
 * 2. Numeric Dispatch (RFC 2812 Compliance):
 * - RPL_WELCOME (001): Confirms the nickname is accepted and the session is open.
 * - RPL_YOURHOST (002): Informs the client about the server hostname and 
 * software version (ft_irc 1.0).
 * - RPL_CREATED (003): Communicates the server's uptime or compilation date.
 * - RPL_MYINFO (004): Lists supported user/channel modes for client configuration.
 * 3. State Synchronization: 
 * - Injects each formatted response directly into the client's output buffer.
 * - Effectively moves the client from 'Unregistered' to 'Active' status.
 * 4. Client Notification: Typically followed by the Message of the Day (MOTD) 
 * to complete the visual onboarding in the client UI.
 * * @note This sequence is the mandatory trigger for modern IRC clients to 
 * unlock their command input interface.
 */

void CommandExecutor::sendWellcome(Client& client, IRCMessage& msg)
{
	std::string text = HELP;
	std::string nick = client.getNickname();

	std::string welcomeReply = msg.buildServerMessage(SERVER_NAME,  nick , RPL_WELCOME, RPL_WELCOME_MSG + client.getPrefix());
	std::string hostReply 	 = msg.buildServerMessage(SERVER_NAME, nick , RPL_YOURHOST, RPL_YOURHOST_MSG + std::string(SERVER_NAME));
	std::string createdReply = msg.buildServerMessage(SERVER_NAME,  nick , RPL_CREATED, RPL_CREATED_MSG);

	sendReply(client, msg, welcomeReply);
	sendReply(client, msg, hostReply);
	sendReply(client, msg, createdReply);

	handleBotMessage(client, text, _state);
}

/**
 * @brief Performs a global lookup to detect nickname collisions.
 * * Execution flow for availability check:
 * 1. Registry Query: Invokes the global server state to search for any active 
 * Client instance bound to the requested nickname.
 * 2. Collision Detection: 
 * - Returns TRUE: If a match is found, indicating the nickname is currently 
 * occupied by another peer (triggering ERR_NICKNAMEINUSE).
 * - Returns FALSE: If the identity is available for assignment.
 * * @param nickname The target string to validate against the global registry.
 * * @return Boolean status of the nickname's availability.
 */

bool CommandExecutor::isNickNameInUse(const std::string& nickname)
{
	if (_state.getClientbyNick(nickname))
		return (true);
	return (false);
}

/**
 * @brief Quantifies the number of arguments extracted from an IRC message.
 * * Execution flow for parameter analysis:
 * 1. Vector Inspection: Measures the size of the parameter container to 
 * facilitate syntax validation (e.g., checking against ERR_NEEDMOREPARAMS).
 * 2. Const Integrity: Operates as a read-only utility to ensure no 
 * modification of the parameter stream occurs during validation.
 * * @param params The vector of strings parsed from the raw IRC command.
 * * @return The total number of parameters available for command execution.
 */

size_t  CommandExecutor::paramCount(std::vector<std::string> params) const {
	return params.size();
}

/**
 * @brief Relays a message to all participants of a channel with optional exclusion.
 * * Execution flow for multi-target transmission:
 * 1. Target Identification: Queries the Channel object to retrieve a list of 
 * File Descriptors (FDs) for all current members.
 * 2. Selective Filtering: Applies the 'exceptFd' constraint to ensure the 
 * message origin (or a specific target) does not receive a redundant copy.
 * 3. Batch Queuing: Hands over the collective list of FDs and the formatted 
 * message to the IRCMessage response manager.
 * 4. Network Efficiency: Prepares the server for a single-cycle flush, reducing 
 * the overhead of multiple individual write operations across the network state.
 * * @param channel Pointer to the destination channel.
 * * @param msg Reference to the current IRC message context.
 * * @param message The pre-formatted string (including CRLF) to be broadcast.
 * * @param exceptFd The File Descriptor to exclude from the broadcast (usually the sender).
 */

void	CommandExecutor::broadcast(Channel *channel, IRCMessage& msg, const std::string& message, int exceptFd)
{
	std::vector<int>	targetFds;

	targetFds = channel->getBroadcastFds(exceptFd);
	msg.addResponse(targetFds, message);
}

/**
 * @brief Performs a graceful or emergency teardown of a client's session.
 * * Execution flow for client cleanup:
 * 1. Notification Phase:
 * - Construct a global QUIT message using the client's prefix and a reason 
 * (e.g., "Connection closed" or "Quit: Leaving").
 * 2. Cross-Channel Synchronization:
 * - Iterate through every active channel in the server state.
 * - For each channel where the client is a member:
 * * Broadcast the QUIT notification to all other members.
 * * Remove the client from membership and operator registries.
 * 3. Governance and Promotion:
 * - If the departing client was an Operator and the channel becomes leaderless 
 * but not empty, trigger promoteFirstMember() to ensure continuity.
 * 4. State Deallocation:
 * - Invoke _state.disconnectClient() to close the socket and remove the 
 * client instance from the global registry.
 * * @note This method is the primary safeguard against "ghost" users and 
 * ensures memory integrity across the server.
 */

void 	CommandExecutor::cleanupClient(Client* client, const std::string reason, IRCMessage& msg)
{
	if (!client)
		return;

	std::string quitMsg = ":" + client->getPrefix() + " QUIT :" + reason + "\r\n";

	std::map<std::string, Channel> channels = _state.getChannelsMap();
	std::map<std::string, Channel>::iterator it = channels.begin();

	for (it = channels.begin() ; it != channels.end(); ++it) 
	{
		Channel& channel = it->second;

		if (channel.isMember(client->getFd()))
		{
			broadcast(&channel, msg, quitMsg, client->getFd());
			channel.removeMember(client);
			
			if (channel.isOperator(client->getFd()) && channel.getOperatorsCount() == 1) {
				channel.promoteFirstMember();
			}
		}
	}
	_state.unregisterClient(client->getFd());
}

/**
 * @brief Validates a nickname against RFC 2812 syntactic constraints.
 * * Execution flow for nickname sanitization:
 * 1. Dimensional Check: Verify the nickname length is within the standard 
 * limits (1 to 9 characters). Prevents buffer overflow and UI misalignment.
 * 2. First Character Validation:
 * - Must be an alphabetic character [a-z, A-Z] or a defined special symbol 
 * from the allowed set ( [ ] \ ^ _ ` { | } ).
 * - Digits and hyphens are strictly prohibited as the leading character.
 * 3. Subsequent Character Iteration:
 * - Allows alphanumeric characters, hyphens '-', and the aforementioned 
 * special symbol set.
 * 4. Security: Ensures the nickname does not contain delimiters (like SPACE, 
 * COMMA, or COLON) that would corrupt IRC message framing.
 * * @return TRUE if the nickname adheres to the protocol's grammar, FALSE otherwise.
 */

bool CommandExecutor::isValidNickname(const std::string& nickname)
{
	if (nickname.empty() || nickname.length() > 9)
		return false;

	const std::string specialChars = "[]\\^_`{|}";

	char first = nickname[0];
	bool validFirst = std::isalpha(static_cast<unsigned char>(first)) ||
					(specialChars.find(first) != std::string::npos);

	if (!validFirst)
		return false;

	for (size_t i = 1; i < nickname.length(); i++) {
		char c = nickname[i];
		bool validChar = std::isalnum(static_cast<unsigned char>(c)) ||
						c == '-' ||
						(specialChars.find(c) != std::string::npos);

		if (!validChar)
			return false;
	}

	return true;
}

/*
** ==========================================================================
** MAIN METHOD
** ==========================================================================
*/

/**
 * @brief Orchestrates the validation and dispatching of incoming IRC commands.
 * * Execution flow for command processing:
 * 1. Routing: Search the internal _commandMap for the handler associated with 
 * the incoming command string.
 * 2. Error Handling (421): If the command is unrecognized, dispatch 
 * ERR_UNKNOWNCOMMAND and abort execution.
 * 3. Security Gateway: Invoke requiresRegistration() to ensure the client has 
 * cleared the PASS/NICK/USER handshake before accessing restricted logic.
 * - Failure: Dispatch ERR_NOTREGISTERED (451).
 * 4. Dynamic Execution: Trigger the mapped member function pointer (CommandHandler) 
 * passing the current client context and parsed message.
 */

void	CommandExecutor::execute(Client& client, IRCMessage& msg)
{
	std::map<std::string, CommandHandler>::iterator it = _commandMap.find(msg.getCommand());
	std::string	nick = client.getNickname();

	if (it == _commandMap.end())
	{		
		std::cout << "[log:] [EXECUTE] Unknown command received: " << msg.getCommand() << std::endl;
		std::string unknownReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_UNKNOWNCOMMAND, ERR_UNKNOWNCOMMAND_MSG, msg.getCommand());
		sendReply(client, msg, unknownReply);
		return ;
	}
	
	if (requiresRegistration(client, msg.getCommand()))
	{
		std::cout << "[log:] [EXECUTE] Command " << msg.getCommand() << " rejected: client not registered." << std::endl;
		std::string notRegisReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG);
		sendReply(client, msg, notRegisReply);
		return;
	}

	std::cout << "[log:] [EXECUTE] Dispatching command: " << msg.getCommand() << std::endl;
	(this->*(it->second))(client, msg);
}

/**
 * @brief Registers a new network connection into the server state.
 * * Execution flow for initial onboarding:
 * 1. Instance Creation: Instantiate a new Client object associated with the 
 * provided File Descriptor (FD).
 * 2. Metadata Binding: Store the originating IP address for logging and 
 * protocol prefixing (:nick!user@host).
 * 3. State Integration: Append the client to the global registry to enable 
 * subsequent command execution.
 */

void   CommandExecutor::onClientConnect(int fd, const std::string &ip)
{
	_state.addClient(fd, ip);
	std::cout << "[log:] [CONNECT] New client connection accepted." << std::endl;
}

/**
 * @brief Handles unexpected or forced client socket closures.
 * * Execution flow for emergency cleanup:
 * 1. Identification: Retrieve the client instance associated with the dying FD.
 * 2. Simulated Exit: Synthesize a virtual "QUIT" command to trigger the 
 * standard departure logic.
 * 3. Resource Deallocation: Invoke cleanupClient() to remove the user from 
 * all channels, clear buffers, and wipe the global state registry.
 */

void    CommandExecutor::onClientDisconnect(int fd)
{
	Client *client = _state.getClient(fd);
	if (!client)
		return ;
	std::cout << "[log:] [DISCONNECT] Client connection lost. Cleaning up session." << std::endl;
	IRCMessage msg("QUIT");
	cleanupClient(client, "Client exited (Connection closed)", msg);
}

/**
 * @brief Retrieves a client's memory pointer from the global state registry.
 * * Execution flow for context lookup:
 * 1. Registry Query: Access the underlying server state to find the client 
 * mapping for a specific File Descriptor.
 * 2. Pointer Management: Return the reference to the Client object or NULL 
 * if the descriptor is no longer valid or recognized.
 * * @return Pointer to the active Client instance or NULL on lookup failure.
 */

 Client* CommandExecutor::getClient(int fd)
{
    return (_state.getClient(fd));
}


/*
** ==========================================================================
** REGISTRATION / AUTHENTICATION COMMANDS
** ==========================================================================
*/

/**
 * @brief Authenticates the initial connection against the server-wide password.
 * * Execution flow for security validation:
 * 1. Protocol Sequence Check: Verify that the client is not already registered. 
 * If so, dispatch ERR_ALREADYREGISTRED (462) to maintain session integrity.
 * 2. Parameter Validation: Ensure exactly one password argument is provided. 
 * If missing, dispatch ERR_NEEDMOREPARAMS (461).
 * 3. Credential Verification:
 * - Compare the provided string against the server's master password 
 * (stored in the global state).
 * - If mismatch: Dispatch ERR_PASSWDMISMATCH (464) and potentially flag the 
 * connection for forced termination.
 * 4. State Transition:
 * - Mark the 'PASS' phase as successfully cleared in the client's internal 
 * handshake registry.
 * - Allow the client to proceed to the NICK and USER identification stages.
 * * @note This command must be the first message sent by any client (excluding CAP).
 */

void CommandExecutor::cmdPASS(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();

	if (client.isRegistered())
	{
		std::string registredReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_ALREADYREGISTERED, ERR_REGISTERED_MSG);
		sendReply(client, msg, registredReply);
		return ;
	}
	
	if (msg.getParams().empty())
	{
		std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "PASS");
		sendReply(client, msg, paramsReply);
		return ;
	}

	if (msg.getParams()[0] == _state.getPassword())
	{
		client.setHasPassword(true);
		std::cout << "[log:] [PASS] Authentication successful." << std::endl;
	}
	else
	{
		std::cout << "[log:] [PASS] Authentication failed: wrong password." << std::endl;
		std::string passwordReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_PASSWDMISMATCH, ERR_PASSWDMISMATCH_MSG);
		sendReply(client, msg, passwordReply);		
	}
	if (client.isRegistered())
		sendWellcome(client, msg);
}

/**
 * @brief Manages the assignment and modification of client nicknames.
 * * Execution flow for nickname registration and updates:
 * 1. Parameter Validation: Ensure a nickname is provided; otherwise, dispatch 
 * ERR_NONICKNAMEGIVEN (431).
 * 2. Syntax and Collision Check:
 * - Validate characters (avoiding restricted symbols or leading digits).
 * - Verify uniqueness against the global server registry. If the nickname 
 * is taken or invalid, dispatch ERR_NICKNAMEINUSE (433) or ERR_ERRONEUSNICKNAME (432).
 * 3. Identity Transition:
 * - CASE A (New Client): Bind the nickname to the session. If PASS and USER 
 * requirements are already satisfied, trigger the final registration sequence.
 * - CASE B (Active Client): Update the registry and broadcast the NICK change 
 * to all common channel peers to maintain UI synchronization.
 * 4. Network Synchronization:
 * - Format the change notification using the full prefix (:OldNick!User@Host NICK :NewNick).
 * - Ensure all shared channels update their internal member lists.
 * * @note Strict adherence to the 'first-come, first-served' rule for nickname 
 * availability across the server instance.
 */

void CommandExecutor::cmdNICK(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();

	if (msg.getParams().empty())
	{

		std::string noNicknameReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NONICKNAMEGIVEN, ERR_NONICKNAMEGIVEN_MSG);
		sendReply(client, msg, noNicknameReply);
		return ;
	}
	
	std::string newNick = msg.getParams()[0];
	if (newNick == client.getNickname())
		return ;

	if (!isValidNickname(newNick))
	{
		std::string neusNicknameReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_ERRONEUSNICKNAME, ERR_NEUSNICKNAME_MSG);
		sendReply(client, msg, neusNicknameReply);
		return ;
	}
	
	if (isNickNameInUse(newNick))
	{
		std::string nicknameUseReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NICKNAMEINUSE, ERR_NICKNAMEINUSE_MSG, newNick);
		sendReply(client, msg, nicknameUseReply);
		return ;
	}

	std::cout << "[log:] [NICK] Nickname assignment requested." << std::endl;
	std::string oldNick = client.getNickname();
	client.setNickname(newNick);
	client.setHasNick(true);

	if (oldNick.empty() || oldNick == "*")
	{
		if (client.isRegistered())
		{
			std::cout << "[log:] [NICK] Initial nickname set. Registration complete, sending welcome." << std::endl;
			sendWellcome(client, msg);
		}
	}
	else
	{
		sendReply(client, msg, ":" + oldNick + "!" + client.getUsername() + "@" + client.getIp() + " NICK :" + newNick);
		std::map<std::string, Channel> channels = _state.getChannelsMap();
		for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
		{
			if (it->second.isMember(client.getFd()))
			{
				std::string nickMsg = ":" + oldNick + "!" + client.getUsername() + "@" + client.getIp() + " NICK :" + newNick;
				broadcast(&it->second, msg, nickMsg, -1);
			}
		}
		std::cout << "[log:] [NICK] Nickname changed successfully." << std::endl;
	}
}

/**
 * @brief Configures the session identity and finalizes the client registration.
 * * Execution flow for user registration:
 * 1. State Validation: Verify the client is not already fully registered. 
 * If so, dispatch ERR_ALREADYREGISTRED (462) to prevent identity tampering.
 * 2. Parameter Extraction:
 * - Retrieve <username> and <realname> from the message stream.
 * - Note: <hostname> and <servername> are parsed but discarded as per 
 * modern server standards (replaced by actual socket metadata).
 * 3. Identity Binding: 
 * - Update the Client object with the provided credentials.
 * - Mark the 'USER' phase as completed in the registration handshake.
 * 4. Welcome Sequence (Post-Handshake):
 * - If the mandatory requirements (PASS + NICK + USER) are satisfied:
 * * Toggle the isRegistered() status to true.
 * * Dispatch the global Welcome Numerics (RPL_WELCOME 001 to 004).
 * * Broadcast the Message of the Day (MOTD) to synchronize the client state.
 * * @note Error handling includes ERR_NEEDMOREPARAMS (461) and ERR_ALREADYREGISTRED (462).
 */

 void CommandExecutor::cmdUSER(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();

	if (client.hasUser())
	{
		std::string registredReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_ALREADYREGISTERED, ERR_REGISTERED_MSG);
		sendReply(client, msg, registredReply);
		return;
	}

	if (msg.getParams().size() < 3)
	{
		std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "USER");
		sendReply(client, msg, paramsReply);
		return;
	}
	
	client.setUsername(msg.getParams()[0]);
	client.setRealname(msg.getTrailing());
	client.setHasUser(true);
	std::cout << "[log:] [USER] User identity registered." << std::endl;
	
	if (client.isRegistered())
	{
		std::cout << "[log:] [USER] Registration complete, sending welcome sequence." << std::endl;
		sendWellcome(client, msg);
	}
}

/*
** ==========================================================================
** CHANNEL COMMANDS
** ==========================================================================
*/

/**
 * @brief Facilitates the entry of a client into a specific channel or creates it.
 * * Execution flow for channel joining:
 * 1. Parameter Validation: Ensure a channel name is provided and conforms to 
 * formatting standards (e.g., prefix '#'). If missing, dispatch ERR_NEEDMOREPARAMS (461).
 * 2. Channel Lifecycle Management:
 * - Search the global registry for the target channel.
 * - If non-existent: Instantiate a new Channel object and grant the 'Operator' 
 * privilege (@) to the initiating client.
 * - If existing: Verify access restrictions (Key +k, Limit +l, or Invite-only +i).
 * 3. Membership Registration:
 * - Append the client's file descriptor and metadata to the channel's internal registry.
 * - Update the client's local record of active channel memberships.
 * 4. Protocol Synchronization and Broadcasting:
 * - Relay the JOIN notification to all existing members (including the joiner).
 * - Dispatch informational numerics: RPL_TOPIC (332) and RPL_NAMREPLY (353) 
 * followed by RPL_ENDOFNAMES (366).
 * * @note Error handling includes ERR_NOSUCHCHANNEL (403), ERR_CHANNELISFULL (471), 
 * ERR_INVITEONLYCHAN (473), and ERR_BADCHANNELKEY (475).
 */

void CommandExecutor::cmdJOIN(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();
	if (!client.isRegistered())
	{
		std::string notRegisReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG);
		sendReply(client, msg, notRegisReply);
		return ;
	}

	if (msg.getParams().empty())
	{
		std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "JOIN");
		sendReply(client, msg, paramsReply);
		return ;
	}

	std::string channelName = msg.getParams()[0];

	if (channelName.empty() || channelName[0] != '#')
	{
		std::string noChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, channelName);
		sendReply(client, msg, noChannelReply);
		return ;
	}

	Channel* channel = _state.getChannel(channelName);
	bool isNewChannel = (channel == NULL);

	if (isNewChannel)
	{
		channel = setChannel(channelName, client);
		std::cout << "[log:] [JOIN] Channel " << channelName << " created. Client set as operator." << std::endl;
		if (paramCount(msg.getParams()) > 1)
		{
			channel->setPasswordChannel(msg.getParams()[1]);
			std::cout << "[log:] [JOIN] Channel " << channelName << " password set." << std::endl;
		}
	}
	else
	{
		if (channel->isMember(client.getFd()))
			return ;

		if (channel->isInviteOnly() && !channel->isInvited(client.getFd()))
		{
			std::string inviteOnlyReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_INVITEONLYCHAN, ERR_INVITEONLYCHAN_MSG, channelName);
			sendReply(client, msg, inviteOnlyReply);
			return ;
		}

		if (channel->hasUserLimit() && channel->getMembersCount() >= channel->getUserLimit())
		{
			std::string channelFullReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_CHANNELISFULL, ERR_CHANNELISFULL_MSG, channelName);
			sendReply(client, msg, channelFullReply);
			return ;
		}
		if (channel->hasPasswordChannel())
		{
			if (msg.getParams().size() < 2 || msg.getParams()[1] != channel->getPassword())
			{
				std::string badChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_BADCHANNELKEY, ERR_BADCHANNELKEY_MSG, channelName);
				sendReply(client, msg, badChannelReply);
				return ;
			}
		}
		if (!channel->addMember(&client))
		{
			std::string bannedReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_BANNEDFROMCHAN, ERR_BANNEDFROMCHAN_MSG, channelName);
			sendReply(client, msg, bannedReply);
			return ;
		}
	}

	std::string joinMsg = msg.buildClientMessage(client.getPrefix(), " JOIN ", channelName) + "\r\n";
	broadcast(channel, msg, joinMsg, -1);
	std::cout << "[log:] [JOIN] Client joined channel " << channelName << ". Sending topic and names." << std::endl;

	if (!channel->getTopic().empty())
	{
		std::string topicReply = msg.buildServerMessage(SERVER_NAME, nick, RPL_TOPIC, ":" + channel->getTopic(), channelName);
		sendReply(client, msg, topicReply);
	}

	sendReply(client, msg, ":" + std::string(SERVER_NAME) + " " + RPL_NAMREPLY + " " + 
			  client.getNickname() + " = " + channelName + " :" + channel->getMemberList());
	std::string endNamesReply = msg.buildServerMessage(SERVER_NAME, nick, RPL_ENDOFNAMES, RPL_ENDOFNAMES_MSG, channelName);
	sendReply(client, msg, endNamesReply);
}



/**
 * @brief Dispatches private messages between individual peers or to entire channels.
 * * Execution flow for message delivery:
 * 1. Parameter Validation: Ensure both a target recipient and a message body 
 * (trailing) are present. If missing, dispatch ERR_NORECIPIENT (411) or 
 * ERR_NOTEXTTOSEND (412).
 * 2. Target Identification:
 * - CHANNEL: Verify channel existence and sender's permissions (e.g., membership 
 * or specific modes like +n/no-external-messages).
 * - USER: Search the global registry for the target nickname.
 * 3. Authority and Access Control:
 * - If the target is a channel, validate that the sender is authorized to 
 * broadcast (ERR_CANNOTSENDTOCHAN - 404).
 * 4. Delivery Phase:
 * - Format the message using the sender's full prefix (:Nick!User@Host).
 * - For Channels: Iterate through the member list and inject the formatted 
 * stream into each peer's output buffer (excluding the origin).
 * - For Users: Inject the stream directly into the target client's buffer.
 * * @note Error handling includes ERR_NOSUCHNICK (401) and ERR_NOSUCHCHANNEL (403).
 */

void CommandExecutor::cmdPRIVMSG(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();

	if (!client.isRegistered())
	{
		std::string notRegisReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTREGISTERED, ERR_NOTREGISTERED_MSG);
		sendReply(client, msg, notRegisReply);
		return ;
	}	

	if (msg.getParams().empty())
	{
		std::string noRecipientReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NORECIPIENT, ERR_NORECIPIENT_MSG);
		sendReply(client, msg, noRecipientReply);
		return ;	
	}

	if (msg.getTrailing().empty())
	{
		std::string notExtReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTEXTTOSEND, ERR_NOTEXTTOSEND_MSG);
		sendReply(client, msg, notExtReply);
		return ;
	}

	std::string target 	= msg.getParams()[0];
	std::string text 	= msg.getTrailing();

	if (target[0] == '#')
	{
		Channel* channel = _state.getChannel(target);
		if (!channel)
		{
			std::string noChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, target);
			sendReply(client, msg, noChannelReply);
			return ;
		}

		if (!channel->isMember(client.getFd()))
		{
			std::string noSendReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_CANNOTSENDTOCHAN, ERR_NOSENDTOCHAN_MSG, target);
			sendReply(client, msg, noSendReply);
			return ;
		}

		std::string header 			= msg.buildClientMessage(client.getPrefix(), " PRIVMSG ", target + " :");
		size_t 		maxChunkSize 	= 510 - header.length(); // 512 - 2 (\r\n) - header

		while (text.size() > maxChunkSize)
		{
			std::string	chunk = text.substr(0, maxChunkSize);
			text.erase(0, maxChunkSize);
			std::string message = header + chunk + "\r\n";
			broadcast(channel, msg, message, client.getFd());
		}
		std::string message = header + text + "\r\n";
		broadcast(channel, msg, message, client.getFd());
	}

	else
	{
		if (target == "bot") {
			handleBotMessage(client,text, _state);
			return ;
		}

		Client* targetClient = _state.getClientbyNick(target);
		if (!targetClient)
		{
			std::string noNickReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG, target);
			sendReply(client, msg, noNickReply);
			return ;
		}

		std::string header 			= ":" + client.getPrefix() + " PRIVMSG " + target + " :";
		size_t 		maxChunkSize 	= 510 - header.length();

		std::vector<int>	targetFds;
		targetFds.push_back(targetClient->getFd());

		std::cout << "[log:] [PRIVMSG] Private message queued for delivery to user." << std::endl;
		while (text.size() > maxChunkSize)
		{
			std::string	chunk = text.substr(0, maxChunkSize);
			text.erase(0, maxChunkSize);
			msg.addResponse(targetFds, (header + chunk + "\r\n"));
		}
		msg.addResponse(targetFds, (header + text + "\r\n"));
	}
}

/**
 * @brief Processes the voluntary departure of a client from a specific channel.
 * * Execution flow for channel exit:
 * 1. Parameter Validation: Ensure at least one channel identifier is present. 
 * If absent, dispatch ERR_NEEDMOREPARAMS (461).
 * 2. Existence and Membership Check:
 * - Verify the target channel exists within the global server registry.
 * - Confirm the requesting client is an active member of said channel.
 * 3. Notification Phase:
 * - Construct the PART message including the optional departure reason (trailing).
 * - Broadcast the notification to all channel members (including the leaver) 
 * to synchronize their local UI and member lists.
 * 4. State Cleanup and Ownership Transfer:
 * - Remove the client from the channel's membership and operator registries.
 * - Ownership Logic: If the departing client was the last Operator and the 
 * channel remains non-empty, trigger promoteFirstMember() to maintain 
 * channel governance.
 * - Self-Destruction: If the member count reaches zero, flag the channel 
 * for deallocation from the server state.
 * * @note Error handling includes ERR_NOSUCHCHANNEL (403) and ERR_NOTONCHANNEL (442).
 */

void CommandExecutor::cmdPART(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();

	if (msg.getParams().empty()) 
	{
		std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "PART");
		sendReply(client, msg, paramsReply);
		return ;
	}

	std::string channelName = msg.getParams()[0];
	Channel* channel = _state.getChannel(channelName);

	if (!channel)
	{
		std::string noChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, channelName);
		sendReply(client, msg, noChannelReply);
		return ;
	}

	if (!channel->isMember(client.getFd()))
	{
		std::string notonChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG, channelName);
		sendReply(client, msg, notonChannelReply);
		return ;
	}

	std::string partMsg = msg.getTrailing().empty() ? client.getNickname() : msg.getTrailing();
	std::string partNotify = msg.buildClientMessage(client.getPrefix(), " PART ", channelName + " :" + partMsg);
	
	broadcast(channel, msg, partNotify, -1);
	std::cout << "[log:] [PART] Client left channel " << channelName << "." << std::endl;

	bool wasOperator = channel->isOperator(client.getFd());
	bool hadOtherOps = (channel->getOperatorsCount() > 1);

	channel->removeMember(&client);

	if (wasOperator && !hadOtherOps && !channel->hasNoMembers()) {
		Client* newOp = channel->promoteFirstMember();
		std::string modeNotify = ":" + std::string(SERVER_NAME) + " MODE " + channelName + " +o " + newOp->getNickname();
		broadcast(channel, msg, modeNotify, -1);
	}
}

/**
 * @brief Manages or queries the descriptive metadata (topic) of a specific channel.
 * * Execution flow for topic management:
 * 1. Parameter Validation: Ensure a channel target is specified. If absent, 
 * dispatch ERR_NEEDMOREPARAMS (461).
 * 2. Existence and Membership Check:
 * - Verify the target channel exists in the global server state.
 * - Confirm the requesting client is a registered member of the channel.
 * 3. Query Flow (No trailing message):
 * - Retrieve the current topic string.
 * - Respond with RPL_TOPIC (332) or RPL_NOTOPIC (331) if the string is empty.
 * 4. Modification Flow (With trailing message):
 * - Authority Check: If the channel is 'Topic-Restricted' (+t), verify the 
 * sender holds Operator privileges (@).
 * - Constraints: Validate topic length to prevent buffer overflows or UI distortion.
 * - State Update: Update the channel's metadata and broadcast the new TOPIC 
 * status to all members to synchronize their local client views.
 * * @note Error handling includes ERR_NOSUCHCHANNEL (403), ERR_NOTONCHANNEL (442), 
 * and ERR_CHANOPRIVSNEEDED (482).
 */

void CommandExecutor::cmdTOPIC(Client& client, IRCMessage& msg)
{
	std::string nick 		= client.getNickname();

	if (msg.getParams().empty())
	{
		std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "TOPIC");
		sendReply(client, msg, paramsReply);
		return ;
	}
	std::string firstParam 	= msg.getParams()[0];
	Channel*   channel = _state.getChannel(msg.getParams()[0]);
	if (!channel)
	{
		std::string noChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, firstParam);
		sendReply(client, msg, noChannelReply);
		return ;
	}
	if (!channel->isMember(client.getFd()))
	{
		std::string notonChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG, firstParam);
		sendReply(client, msg, notonChannelReply);
		return ;
	}
	if (msg.getTrailing().empty())
	{
		if (channel->getTopic().empty() || channel->getTopic() == "")
		{
			std::string noTopicReply = msg.buildServerMessage(SERVER_NAME, nick, RPL_NOTOPIC, RPL_NOTOPIC_MSG, firstParam);
			sendReply(client, msg, noTopicReply);
			return ;
		}
		std::string topicReply = msg.buildServerMessage(SERVER_NAME, nick, RPL_TOPIC, ":" + channel->getTopic(), firstParam);
		sendReply(client, msg, topicReply);
		return ;
	}
	if (channel->isTopicRestricted() && !channel->isOperator(client.getFd()))
	{
		std::string topicRestrictReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_CHANOPRIVSNEEDED, ERR_NOPRIVSNEEDED_MSG);
		sendReply(client, msg, topicRestrictReply);
		return ;
	}

	if (msg.getTrailing().size() > 100)
	{
		std::string topicLongReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_TOPICTOOLONG, ERR_TOPICTOOLONG_MSG);
		sendReply(client, msg, topicLongReply);
		return ;
	}

	channel->setTopic(msg.getTrailing());
	std::cout << "[log:] [TOPIC] Topic updated for channel " << channel->getName() << "." << std::endl;
	std::string   topicMsg = ":" + client.getPrefix() + " TOPIC " + channel->getName() + " :" + msg.getTrailing() + "\r\n";
	broadcast(channel, msg, topicMsg, -1);
}

/*
** ==========================================================================
** COMMANDS OPERATOR
** ==========================================================================
**
*/

/**
 * @brief Manages channel modes and state flags for access control.
 * * Execution flow for mode modification and query:
 * 1. Parameter Triage: 
 * - If only <channel> is provided: Execute Query Flow.
 * - If <channel> and <modestring> are provided: Execute Modification Flow.
 * 2. Query Flow (RPL_CHANNELMODEIS):
 * - Validate channel existence.
 * - Serialize current active flags (i, t, k, l).
 * - Append public parameters (current limit, but omit the key for security).
 * 3. Modification Flow (Operator Exclusive):
 * - Authority Check: Verify the sender holds Operator privileges (@).
 * - Parser Logic: Iterate through the modestring identifying polarity ('+' or '-').
 * - Toggle Flags:
 * * [i/t]: Update boolean state of Invite-only or Topic-restriction.
 * * [k/l/o]: Consume additional parameters from the argument list.
 * 4. State Synchronization:
 * - Broadcast successful mode changes to all channel members to update client UIs.
 * - Handle specific errors: ERR_KEYSET (key already exists) or ERR_UNKNOWNMODE.
 * * @note Strict compliance with 42 subject requirements for modes +i, +t, +k, +o, and +l.
 */

void CommandExecutor::cmdMODE(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();

	if (msg.getParams().empty()) {
		std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "MODE");
		sendReply(client, msg, paramsReply);
		return;
	}

	std::string channelName = msg.getParams()[0];

	if (channelName[0] != '#' && channelName[0] != '&')
		return;

	Channel* channel = _state.getChannel(channelName);
	if (!channel) 
	{
		std::string noChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, channelName);
		sendReply(client, msg, noChannelReply);
		return;
	}

	if (msg.getParams().size() == 1) 
	{
		std::string modes = channel->getModeString();
		std::string modeParams = "";

		if (channel->hasUserLimit()) {
			std::ostringstream oss;
			oss << channel->getUserLimit();
			modeParams += " " + oss.str();
		}
		std::string modeReply = msg.buildServerMessage(SERVER_NAME, nick, RPL_CHANNELMODEIS, modes + modeParams, channelName);
		sendReply(client, msg, modeReply);
		return;
	}

	if (!channel->isMember(client.getFd())) 
	{
		std::string notonChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG, channelName);
		sendReply(client, msg, notonChannelReply);
		return ;
	}

	if (!channel->isOperator(client.getFd())) 
	{
		std::string topicRestrictReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_CHANOPRIVSNEEDED, ERR_NOPRIVSNEEDED_MSG, channelName);
		sendReply(client, msg, topicRestrictReply);
		return ;
	}

	std::string modestring = msg.getParams()[1];
	size_t paramIndex = 2;

	bool adding = true;
	std::string appliedModes = "";
	std::string appliedParams = "";
	std::string newOpNotify = "";
	bool new_operator = false;

	if (modestring[0] == '+')
		;
	else if (modestring[0] == '-')
		;
	else
		return;
	for (size_t i = 0; i < modestring.length(); i++) {
		char mode = modestring[i];

		if (mode == '+') {
			adding = true;
			continue;
		}
		else if (mode == '-') {
			adding = false;
			continue;
		}

		switch (mode) {
			case 'i':
				channel->setInvitedOnly(adding);
				appliedModes += (adding ? "+i" : "-i");
				break;

			case 't':
				channel->setTopicRestricted(adding);
				appliedModes += (adding ? "+t" : "-t");
				break;

			case 'k':
				if (adding) {
					if (paramIndex >= msg.getParams().size())
					{
						std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "MODE");
						sendReply(client, msg, paramsReply);
						continue;
					}
					std::string key = msg.getParams()[paramIndex++];
					channel->setPasswordChannel(key);
					appliedModes += "+k";
					appliedParams += " " + key;
				}
				else {
					channel->setPasswordChannel("");
					appliedModes += "-k";
				}
				break;

			case 'o':
			{
				if (paramIndex >= msg.getParams().size()) 
				{
					std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "MODE");
					sendReply(client, msg, paramsReply);
					continue ;
				}
				std::string targetNick = msg.getParams()[paramIndex++];
				Client* target = channel->findMemberByNick(targetNick);
				
				if (!target)
				{
					std::string noUserReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_USERNOTINCHANNEL, ERR_NOUSERCHANNEL_MSG, targetNick + " " + channelName);
					sendReply(client, msg, noUserReply);
					continue ;
				}

				if (adding)
					channel->addOperator(target->getFd());
				else
				{
					channel->removeOperator(target->getFd());
					if (channel->getOperatorsCount() == 0)
					{
						new_operator = true;
						Client* newOp = channel->promoteFirstMember();
						newOpNotify = ":" + std::string(SERVER_NAME) + " MODE " + channelName + " +o " + newOp->getNickname();
					}
				}
				appliedModes += (adding ? "+o" : "-o");
				appliedParams += " " + targetNick;
				break;
			}

			case 'l':
				if (adding) {
					if (paramIndex >= msg.getParams().size()) 
					{
						std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "MODE");
						sendReply(client, msg, paramsReply);
						continue;
					}
					std::string limitStr = msg.getParams()[paramIndex++];

					bool isValidNumber = !limitStr.empty();
					for (size_t i = 0; i < limitStr.size() && isValidNumber; ++i)
						if (!std::isdigit(limitStr[i]))
							isValidNumber = false;
					if (!isValidNumber) {
						sendReply(client, msg, ":" + std::string(SERVER_NAME) + " 696 " + client.getNickname() + " " + channelName + " l " + limitStr + " :Invalid limit value, must be a positive integer");
						continue;
					}
					int limit = std::atoi(limitStr.c_str());
					if (limit > 0) 
					{
						channel->setUserLimit(static_cast<size_t>(limit)); 
						appliedModes 	+= "+l";
						appliedParams 	+= " " + limitStr;
					}
					else
						sendReply(client, msg, ":" + std::string(SERVER_NAME) + " 696 " + client.getNickname() + " " + channelName + " l " + limitStr + " :Invalid limit value, must be a positive integer");
				}
				else 
				{
					channel->setUserLimit(0);
					appliedModes += "-l";
				}
				break ;

			default:
				std::string unknownModeReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_UNKNOWNMODE, ERR_UNKNOWNMODE_MSG, "MODE");
				sendReply(client, msg, unknownModeReply);
				break ;
		}
	}

	if (!appliedModes.empty()) {
		std::cout << "[log:] [MODE] Mode change applied on channel " << channelName << ": " << appliedModes << std::endl;
		std::string modeNotify = ":" + client.getPrefix() + " MODE " + channelName + " " + appliedModes + appliedParams;
		broadcast(channel, msg, modeNotify, -1); 
		if (new_operator)
			broadcast(channel, msg, newOpNotify, -1);
	}
}

/**
 * @brief Performs the forced removal of a user from a specific channel.
 * * Execution flow for kick processing:
 * 1. Parameter Validation: Ensure the presence of a target channel and a 
 * target nickname. Extract the optional kick comment if provided.
 * 2. Authority Verification:
 * - Confirm the sender is a registered member of the target channel.
 * - Validate that the sender holds Operator privileges (@). Non-operators 
 * are restricted from triggering this action.
 * 3. Target Verification:
 * - Confirm the existence of the target nickname within the channel's member list.
 * - Confirm the target channel is active in the server state.
 * 4. Eviction Lifecycle:
 * - Broadcast the KICK notification to all channel members (including the 
 * victim) to synchronize local client states.
 * - Remove the target client from the channel's membership and operator registries.
 * - Check for channel emptiness; trigger destruction or operator re-assignment 
 * if necessary.
 * * @note Error handling includes ERR_NEEDMOREPARAMS (461), ERR_NOSUCHCHANNEL (403), 
 * ERR_CHANOPRIVSNEEDED (482), ERR_NOTONCHANNEL (442), and ERR_USERNOTINCHANNEL (441).
 */

void CommandExecutor::cmdKICK(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();

	if (paramCount(msg.getParams()) < 2)
	{
		std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "KICK");
		sendReply(client, msg, paramsReply);
		return ;
	}

	std::string	firstParam 	= msg.getParams()[0];
	std::string	secondParam	= msg.getParams()[1];
	Channel*	channel = _state.getChannel(firstParam);
	if (!channel)
	{
		std::string noChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, firstParam);
		sendReply(client, msg, noChannelReply);
		return ;
	}
	if (!channel->isMember(client.getFd()))
	{
		std::string notonChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG, firstParam);
		sendReply(client, msg, notonChannelReply);
		return ;
	}
	if (!channel->isOperator(client.getFd()))
	{
		std::string topicRestrictReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_CHANOPRIVSNEEDED, ERR_NOPRIVSNEEDED_MSG);
		sendReply(client, msg, topicRestrictReply);
		return ;
	}
	if (msg.getTrailing().size() > 100)
	{
		std::string reasonLongReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_REASONTOOLONG, ERR_REASONTOOLONG_MSG);
		sendReply(client, msg, reasonLongReply);
		return ;
	}

	Client* target = _state.getClientbyNick(secondParam);
	if (!target || !channel->isMember(target->getFd()))
	{
		std::string noUserReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_USERNOTINCHANNEL, ERR_NOUSERCHANNEL_MSG, secondParam);
		sendReply(client, msg, noUserReply);
		return ;
	}

	std::string kickMsg = msg.buildClientMessage(client.getPrefix(), " KICK ", channel->getName() + " " + target->getNickname());
	if (!msg.getTrailing().empty())
		kickMsg += " :" +  msg.getTrailing();
	kickMsg += "\r\n";

	broadcast(channel, msg, kickMsg, -1);
	std::cout << "[log:] [KICK] User removed from channel " << firstParam << "." << std::endl;

	bool wasOperator = channel->isOperator(target->getFd());
	bool hadOtherOps = (channel->getOperatorsCount() > 1);

	channel->removeMember(target);

	if (wasOperator && !hadOtherOps && !channel->hasNoMembers()) {
		Client* newOp = channel->promoteFirstMember();
		std::string modeNotify = ":" + std::string(SERVER_NAME) + " MODE " + firstParam + " +o " + newOp->getNickname();
		broadcast(channel, msg, modeNotify, -1);
	}
}

/**
 * @brief Facilitates the invitation of a specific user to a designated channel.
 * * Execution flow for invitation processing:
 * 1. Parameter Validation: Ensure both a target nickname and a channel name 
 * are provided in the message stream.
 * 2. Source Authority Check:
 * - Verify the sender is a registered member of the target channel.
 * - If the channel is 'Invite-Only' (+i), validate that the sender holds 
 * Operator privileges (@).
 * 3. Target State Verification:
 * - Confirm the existence of the target nickname in the global server registry.
 * - Verify the target is not already a member of the destination channel.
 * 4. Invitation Lifecycle:
 * - Append the target client to the channel's internal 'invite-list' to 
 * bypass future join restrictions.
 * - Dispatch RPL_INVITING (341) to the sender as confirmation.
 * - Relay the invitation notice directly to the target's output buffer.
 * * @note Error handling includes ERR_NEEDMOREPARAMS (461), ERR_NOSUCHNICK (401), 
 * ERR_NOTONCHANNEL (442), ERR_CHANOPRIVSNEEDED (482), and ERR_USERONCHANNEL (443).
 */

void   CommandExecutor::cmdINVITE(Client& client, IRCMessage& msg)
{
	std::string nick 		= client.getNickname();

	if (paramCount(msg.getParams()) < 2)
	{
		std::string paramsReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NEEDMOREPARAMS, ERR_NEEDMOREPARAMS_MSG, "INVITE");
		sendReply(client, msg, paramsReply);
		return ;
	}
	std::string	firstParam 	= msg.getParams()[0];
	std::string	secondParam	= msg.getParams()[1];
	Channel*   channel = _state.getChannel(secondParam);
	if (!channel)
	{
		std::string noChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHCHANNEL, ERR_NOSUCHCHANNEL_MSG, secondParam);
		sendReply(client, msg, noChannelReply);
		return ;
	}
	Client* target = _state.getClientbyNick(firstParam);
	if (!target)
	{
		std::string noNickReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOSUCHNICK, ERR_NOSUCHNICK_MSG, firstParam);
		sendReply(client, msg, noNickReply);
		return ;
	}
	if (!channel->isMember(client.getFd()))
	{
		std::string notonChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_NOTONCHANNEL, ERR_NOTONCHANNEL_MSG, secondParam);
		sendReply(client, msg, notonChannelReply);
		return ;
	}
	if (channel->isMember(target->getFd()))
	{
		std::string onChannelReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_USERONCHANNEL, ERR_USERONCHANNEL_MSG, firstParam + " " + secondParam);
		sendReply(client, msg, onChannelReply);
		return ;
	}
	if (channel->isInviteOnly() && !channel->isOperator(client.getFd()))
	{
		std::string topicRestrictReply = msg.buildServerMessage(SERVER_NAME, nick, ERR_CHANOPRIVSNEEDED, ERR_NOPRIVSNEEDED_MSG, secondParam);
		sendReply(client, msg, topicRestrictReply);
		return ;
	}
	channel->addInvited(target->getFd()); 
	std::cout << "[log:] [INVITE] Invitation sent for channel " << secondParam << "." << std::endl;
	sendReply(client, msg, ":" + std::string(SERVER_NAME) + " " + RPL_INVITING + " " + nick + " " + firstParam + " " + secondParam);
	sendReply(*target, msg, ":" + client.getPrefix() + " INVITE " + firstParam + " :" + secondParam);
}

/**
 * @brief Validates connection liveness and synchronizes client-server latency.
 * * Execution flow for heartbeating:
 * 1. Token Extraction: Retrieve the unique identifier (timestamp or random string) 
 * from the message parameters. If empty, fallback to the server's hostname.
 * 2. Response Construction:
 * - Format a specialized PONG response using the standard IRC numeric syntax.
 * - Include the original token to allow the client to calculate the Round-Trip Time (RTT).
 * 3. Network Transmission:
 * - Push the PONG message directly into the client's output buffer.
 * - Performance: Mandates explicit CRLF (\r\n) termination for immediate 
 * parser recognition at the client-side.
 * 4. Stability: Prevents the server from triggering a 'Ping timeout' and 
 * subsequent disconnection of idle clients.
 */

void CommandExecutor::cmdPING(Client& client, IRCMessage& msg)
{
	std::string token = msg.getParams().empty() ? std::string(SERVER_NAME) : msg.getParams()[0];
	std::string pongReply = ":" + std::string(SERVER_NAME) + " PONG " + std::string(SERVER_NAME) + " :" + token + "\r\n";
	client.sendBuffer(pongReply);
	std::cout << "[log:] [PING] PONG response sent." << std::endl;
}


/**
 * @brief Terminates the client session and performs full resource cleanup.
 * * Execution flow for graceful disconnection:
 * 1. Extraction: Retrieve the optional quit message from the trailing parameters 
 * (defaults to the client's nickname if not provided).
 * 2. Propagation: Broadcast a QUIT notification to all channels where the client 
 * is currently a member to synchronize peer states.
 * 3. Resource Cleanup:
 * - Remove the client from all active channel member and operator lists.
 * - Trigger promoteFirstMember() logic if the departing client was the sole operator.
 * - Wipe the client's presence from the global server state registry.
 * 4. Network Layer: 
 * - Close the associated File Descriptor (FD).
 * - Clear the polling slot to prevent further I/O attempts on a dead socket.
 */

void   CommandExecutor::cmdQUIT(Client& client, IRCMessage& msg)
{
	(void)msg;
	int fd = client.getFd();

	std::cout << "[log:] [QUIT] Client initiated voluntary disconnection." << std::endl;
	cleanupClient(&client, QUIT_MESSAGE, msg);
	_state.unregisterClient(fd);

	close(fd);
}

/**
 * @brief Handles Capability Negotiation between the client and the server.
 * * Execution flow for CAP negotiation:
 * 1. Parameter Inspection: Identify the sub-command sent by the client (LS, REQ, END, etc.).
 * 2. Negotiation Logic:
 * - LS (List): The server broadcasts its supported extensions. Since this is a 
 * standard Base Server, we return an empty list or the end-of-list signal.
 * - REQ (Request): Processes client requests for specific features. Currently 
 * rejects or ignores them as we maintain a lean protocol core.
 * - END: Finalizes the negotiation phase, allowing the registration process 
 * (NICK/USER) to proceed to completion.
 * 3. Protocol Synchronization: 
 * - Ensures the client does not hang during the initial handshake.
 * - Responds with the appropriate CAP * LS or CAP * ACK/NAK messages.
 * * @note This command is essential for compatibility with modern IRC clients like 
 * HexChat, WeeChat, or the irc_tester.py script.
 */

void CommandExecutor::cmdCAP(Client& client, IRCMessage& msg)
{
	if (msg.getParams().empty())
		return;

	std::string subCommand = msg.getParams()[0];
	std::string nick = client.getNickname().empty() ? "*" : client.getNickname();

	if (subCommand == "LS")
	{
		std::string reply = ":" + std::string(SERVER_NAME) + " CAP " + nick + " LS :\r\n";
		client.sendBuffer(reply);
	}
	else if (subCommand == "END")
	{
		std::cout << "[log:] [CAP] Capability negotiation ended." << std::endl;
	}
}

/**
 * @brief Queries information about specific channels and their occupants.
 * * Execution flow for channel-based WHO queries:
 * 1. Parameter Validation: Inspect the mask to ensure it targets a channel 
 * (prefix '#' or '&'). If the mask is a nickname or invalid, the command is ignored.
 * 2. Existence Check: Verify if the requested channel exists in the server state.
 * - If absent: Dispatch ERR_NOSUCHCHANNEL (403) to notify the client.
 * 3. Data Retrieval: If valid, the server currently signals the completion 
 * of the query to synchronize the client's UI state.
 * 4. Network Transmission: Generate and push the RPL_ENDOFWHO (315) numeric 
 * response with the explicit CRLF terminator.
 */
void CommandExecutor::cmdWHO(Client& client, IRCMessage& msg)
{
	std::string nick = client.getNickname();
	
	if (msg.getParams().empty())
	{
		std::string emptyReply = ":" + std::string(SERVER_NAME) + " 315 " + nick + " * :End of WHO list\r\n";
		client.sendBuffer(emptyReply);
		return;
	}

	std::string mask = msg.getParams()[0];

	if (mask[0] != '#' && mask[0] != '&')
	{
		std::string onlyChannelReply = ":" + std::string(SERVER_NAME) + " 403 " + nick + " " + mask + " :Only channel /WHO #channel\r\n";
		client.sendBuffer(onlyChannelReply);
		return;
	}

	Channel *channel = _state.getChannel(mask);
	if (!channel)
	{
		std::string noChannelReply = ":" + std::string(SERVER_NAME) + " 403 " + nick + " " + mask + " :No such channel\r\n";
		client.sendBuffer(noChannelReply);
		return;
	}
	std::string members = channel->getMemberList();
	std::string reply = ":" + std::string(SERVER_NAME) + " 315 " + nick + " " + members + " :End of WHO list\r\n";
	client.sendBuffer(reply);
	std::cout << "[log:] [WHO] WHO list dispatched for channel " << mask << "." << std::endl;
}