/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juagomez <juagomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:51:33 by jumarque          #+#    #+#             */
/*   Updated: 2026/05/12 17:34:21 by juagomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <signal.h>
#include <string.h>
#include <errno.h>
#include "./Server.hpp"

#define CTRL_C_MSG 	"[log: ][!] Execution interrupted (Ctrl+C)."
#define KILL_MSG 	"[log: ][!] Termination signal received"

extern volatile sig_atomic_t glb_keeprunning;

void	setupSignals(void);

/*
** SIGNAL HANDLING - System Event Interception
** ===============================================================================
** This module manages the server's response to external system signals, 
** ensuring a graceful shutdown and preventing resource or port leakage.
**
** GLOBAL STATE:
** -------------
** - glb_keeprunning: A volatile sig_atomic_t flag that acts as the heartbeat 
** of the server. When set to 0, the main execution loop terminates safely.
**
** HANDLED SIGNALS:
** ----------------
** 1. SIGINT (Ctrl+C):  Triggered by the user to interrupt execution. 
** Signals the server to stop accepting new data and begin cleanup.
** 2. SIGTERM (kill):   Standard termination signal used by the system 
** to request a process shutdown.
** 3. SIGTSTP (Ctrl+Z): Specifically ignored (SIG_IGN) to prevent the process 
** from suspending while holding the port binding active.
**
** DESIGN CONSIDERATIONS:
** ----------------------
** - Thread Safety: Uses sig_atomic_t to guarantee that flag updates are 
** atomic and safe from signal handler interruptions.
** - Port Stability: By managing signals correctly, the server avoids the 
** "Address already in use" error by ensuring sockets are closed properly 
** before the process exits.
** - User Feedback: Provides terminal alerts (CTRL_C_MSG / KILL_MSG) to 
** confirm the shutdown sequence has been initiated.
*/