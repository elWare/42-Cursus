/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:51:53 by jumarque          #+#    #+#             */
/*   Updated: 2026/05/05 13:52:03 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>
#include <string>

#include "./Client.hpp"
#include "./IRCModel.hpp"

#define BOTNAME "bot"

void		initBot(Client &bot);
std::string	getTime();
class IRCModel;

void		handleBotMessage(Client &sender, std::string &text, IRCModel& server);

/**
 * @brief Parses and executes automated triggers based on private messages.
 * * Execution flow for bot interaction:
 * 1. Command Triage: Evaluates the incoming 'text' against a suite of 
 * supported triggers (!help, !time, !hi, !joke, etc.).
 * 2. Data Retrieval: Accesses the IRCModel (server) to query real-time 
 * channel states and membership lists.
 * 3. Response Synthesis:
 * - Utility: Provides timestamps and help menus.
 * - Social: Simulates basic conversational responses.
 * - Intelligence: Iterates through the server's channel registry to list 
 * available channels or active "buddies" in shared contexts.
 * 4. Dispatch: Injects the generated responses into the sender's buffer using 
 * the standard PRIVMSG protocol format.
 * * @param sender The client requesting the bot service.
 * * @param text The raw command string sent by the user.
 * * @param server Reference to the global state for data-driven commands.
 */