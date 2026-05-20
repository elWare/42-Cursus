/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumarque <jumarque@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:57:28 by jumarque          #+#    #+#             */
/*   Updated: 2026/05/13 12:17:45 by jumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Bot.hpp"

/**
 * @brief Configures the internal state and credentials of the system bot.
 * * Operational Logic:
 * 1. Identity Binding: Sets the mandatory IRC parameters (Nickname, Username, Realname) 
 * using predefined constants (BOTNAME).
 * 2. Automated Registration: Forces the registration flags (HasPassword, HasNick, HasUser) 
 * to 'true' to bypass the standard handshake and enable immediate interaction.
 * 3. System Integration: Prepares the Client object to act as a virtual entity 
 * within the server's communication model.
 * * @param bot Reference to the Client object that will represent the bot.
 */

void	initBot(Client &bot)
{
	bot.setNickname(BOTNAME);
	bot.setUsername("IRCBot");
	bot.setRealname("The IRC Bot");
	bot.setHasPassword(true);
	bot.setHasNick(true);
	bot.setHasUser(true);
}

/**
 * @brief Generates a formatted timestamp string for bot responses.
 * * Operational Logic:
 * 1. Chronos Retrieval: Fetches the current system time using std::time.
 * 2. Local Conversion: Converts the raw time into a local calendar structure (tm).
 * 3. Formatting: Serializes the date and time into the "YYYY-MM-DD HH:MM:SS" 
 * format using a temporary buffer.
 * * @return A string containing the precisely formatted current date and time.
 */

std::string getTime()
{
	std::time_t now = std::time(NULL);
	std::tm* localTime = std::localtime(&now);

	char buffer[20];

	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

	return std::string(buffer);
}
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

void	handleBotMessage(Client &sender, std::string &text, IRCModel &server){
	
	if (text == "!help")
	{
		sender.sendBuffer(
			":bot PRIVMSG " + sender.getNickname() +
			" :Options are !help, !time, !hi, !joke, !channels, !buddies, !mychannels" + "\r\n"
		);
	}
	else if (text == "!time")
	{
		sender.sendBuffer(
			":bot PRIVMSG " + sender.getNickname() +
			" :Current time is " + getTime() + "\r\n"
		);
	}
	else if (text == "!hi")
	{
		sender.sendBuffer(
			":bot PRIVMSG " + sender.getNickname() +
			" :Hi, How are you? :)" + "\r\n"
		);
	}
	else if (text == "!joke")
	{
		sender.sendBuffer(
			":bot PRIVMSG " + sender.getNickname() +
			" :Because light attracts bugs. 🐛!" + "\r\n"
		);
	}
	else if (text == "!channels")
	{
		std::map<std::string, Channel> mapChannels = server.getChannelsMap();

		std::map<std::string, Channel>::iterator it;
		sender.sendBuffer(":bot PRIVMSG " + sender.getNickname() + " :These are the channels!\r\n");
		for (it = mapChannels.begin(); it != mapChannels.end(); ++it)
		{
			std::string channelName = it->first;
			sender.sendBuffer(":bot PRIVMSG " + sender.getNickname() + " :" + it->first + "\r\n");
		}
		
	}
	else if (text == "!mychannels")
	{
		std::map<std::string, Channel> mapChannels = server.getChannelsMap();
		std::map<std::string, Channel>::iterator it;

		sender.sendBuffer(":bot PRIVMSG " + sender.getNickname() + " :These are my channels!" + "\r\n");

		for (it = mapChannels.begin(); it != mapChannels.end(); ++it)
		{
			std::string channelName = it->first;
			Channel& channel = it->second;
			if (channel.isMember(sender.getFd()))
				sender.sendBuffer(":bot PRIVMSG " + sender.getNickname() + " :" + it->first + "\r\n");
		}
		
	}
	else if (text == "!buddies")
	{
		std::map<std::string, Channel> mapChannels = server.getChannelsMap();

		std::map<std::string, Channel>::iterator it;

		sender.sendBuffer(
			":bot PRIVMSG " + sender.getNickname() +
			" :These are the people in the channels I'm in!" + "\r\n"
		);
		
		for (it = mapChannels.begin(); it != mapChannels.end(); ++it)
		{
			std::string channelList = "";
			std::string channelName = it->first;
			Channel& channel = it->second;
			if (channel.isMember(sender.getFd()))
			{
				channelList += channelName;
				channelList += "->";
				channelList += "[" + channel.getMemberList() + "]";
				sender.sendBuffer(":bot PRIVMSG " + sender.getNickname() + " :" + channelList + "\r\n");
			}
		}
		
	}
	else
	{
		sender.sendBuffer(
			":bot PRIVMSG " + sender.getNickname() +
			" :Did you mean \"!help\" " + getTime() + "\r\n"
		);
	}
}
