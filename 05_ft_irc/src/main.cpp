/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:03:17 by juagomez          #+#    #+#             */
/*   Updated: 2026/05/13 12:11:26 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <string>
# include <sstream>
# include <csignal>

# include "../includes/Signal.hpp"
# include "../includes/Server.hpp"
# include "../includes/IRCModel.hpp"
# include "../includes/CommandExecutor.hpp"

int	validatePort(const std::string &str);

int	main(int argc, char **argv)
{
	std::signal(SIGPIPE, SIG_IGN);
	if (argc != 3)
	{
		std::cerr << NUMBER_ARGS_ERROR << std::endl;
		return (ERROR);
	}
	std::string	password 	= argv[2];	
	int			port 		= validatePort(argv[1]);
	if (port == FAILURE)
		return (ERROR);		   

	setupSignals();	
	
	IRCModel			model(password);
	CommandExecutor		executor(model);
	Server 				server(port, executor);

	int init_status = server.initServer();
	if (init_status == ERROR)
	{
		std::cerr << SOCKET_SYSTEMCALL_ERROR << std::endl;
		return (ERROR);
	}
	int serverState = server.run();	
	if (serverState == ERROR)
	{
		std::cerr << SERVER_LOOP_ERROR << std::endl;
		return (ERROR);
	}
	return (SUCCESS);
}

/*
** MAIN ENTRY POINT - IRC Server Bootstrap
** ===============================================================================
** The entry point coordinates the initialization sequence of the IRC server,
** managing dependency injection between the Model, Executor, and Network layers.
**
** EXECUTION WORKFLOW:
** -------------------
** 1. Signal Pre-configuration: 
** - SIGPIPE is ignored to prevent process termination when writing to a 
** socket that has been closed by the client.
** - setupSignals() is invoked to manage SIGINT/SIGTERM for clean shutdowns.
** 2. Parameter Validation:
** - Validates the CLI arguments (Port and Password).
** - Port undergoes range and type checks via validatePort().
** 3. Component Orchestration (MVC-like Pattern):
** - IRCModel (Model): Stores the global state and server password.
** - CommandExecutor (Controller): Links protocol commands to state changes.
** - Server (View/Network): Manages the poll() loop and low-level I/O.
** 4. Server Lifecycle:
** - initServer(): Performs socket creation, binding, and listening.
** - run(): Enters the non-blocking execution loop until a signal is received.
**
** ERROR HANDLING:
** ---------------
** - Implements strict exit codes (SUCCESS/ERROR) and logs specific system 
** failures (Socket creation, Binding, or Runtime loops) to stderr.
*/


//_____________________________________________________________________________

/**
 * @brief Validates and sanitizes the server port provided via command line.
 * * * Execution Logic (C++09 Stringstream Approach):
 * 1. Type Conversion: Uses std::stringstream to attempt extraction of an integer.
 * The 'trash' char check ensures no trailing non-numeric characters (e.g., "6667a") 
 * are present.
 * 2. Absolute Range Validation: Verifies the port is within the 16-bit unsigned 
 * integer limit (1 - 65535).
 * 3. Network Policy Enforcement:
 * - Rejects System Ports (1-1023): Prevents the need for root privileges and 
 * conflicts with standard services (SSH, HTTP).
 * - Rejects Dynamic Ports (49152-65535): Avoids ranges reserved for ephemeral 
 * client-side connections.
 * 4. Recommended Range: Restricts usage to 'Registered Ports' (1024-49151) for 
 * maximum compatibility and stability.
 * * @param str The raw port string from argv[1].
 * @return The validated port integer if successful, or FAILURE (-1) if validation fails.
 */

int	validatePort(const std::string &str)
{	
	std::stringstream	ss(str);
	int					port;
	char				trash;
	
	if (!(ss >> port) || (ss >> trash))
	{
		std::cerr << CONVERSION_ERROR << std::endl;
		return (FAILURE);
	}
	if (port < 1 || port > 65535)
	{
		std::cerr << OUTRANGE_PORTS_ERROR << std::endl;
		return (FAILURE);
	}	
	if ((port >= 1 && port <= 1023)
		|| (port >= 49152 && port <= 65535))
	{
		std::cerr << PORTS_RANGE_RECOMMENDED << std::endl;
		return (FAILURE);
	}		
	return (port);
}
