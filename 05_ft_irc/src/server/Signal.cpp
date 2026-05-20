/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:48:14 by jumarque          #+#    #+#             */
/*   Updated: 2026/05/12 21:10:33 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Signal.hpp"

volatile sig_atomic_t	glb_keeprunning = 1;

/**
 * @brief Signal handler for system interrupt events.
 * 
 * Overrides default system termination behavior. Sets the global execution flag 
 * (glb_keeprunning) to 0, which breaks the main server poll loop to trigger 
 * a safe resource cleanup and shutdown.
 * 
 * @param sign The integer code of the system signal received (e.g., 2 for SIGINT).
 */
static void	handlerInt(int sign)
{
    glb_keeprunning = 0; 
    
    if (sign == 2)
        std::cout << CTRL_C_MSG << std::endl;
    else
        std::cout << KILL_MSG << std::endl;
}

/**
 * @brief Configures system signal interceptions for graceful shutdown.
 * 
 * Execution Steps:
 * 1. Initializes a sigaction structure and zeroes its memory block to avoid garbage values.
 * 2. Binds the custom 'handlerInt' function to manage incoming interruptions.
 * 3. Clears the signal mask (sigemptyset) to prevent blocking other signals during execution.
 * 4. Enables the custom action intercepting SIGINT (Ctrl + C) and SIGTERM (kill commands).
 */

 /**
     * @note SIGTSTP (Ctrl + Z) Management:
     * By ignoring this signal, we prevent the server from entering a 'Stopped' state
     * where it can't execute code but still holds the port binding.
*/

void	setupSignals(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = handlerInt; 
    sigemptyset(&sa.sa_mask); 
    sa.sa_flags = 0; 

    sigaction(SIGINT, &sa, NULL); 
    sigaction(SIGTERM, &sa, NULL); 

	sa.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &sa, NULL);
}

