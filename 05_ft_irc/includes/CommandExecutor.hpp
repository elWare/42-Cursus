
#pragma once

# include <iostream>
# include <string>
# include <unistd.h>
# include <cstdlib>
# include <map>

# include "./Server.hpp" 
# include "./IRCMessage.hpp"
# include "./IRCModel.hpp"
# include "./Bot.hpp"

// FORWARD DECLARATION
class Server;

/// STANDARD REPLY CODES
#define RPL_WELCOME				"001"
#define	RPL_YOURHOST			"002"
#define	RPL_CREATED				"003"
#define	RPL_MYINFO				"004"
#define	RPL_CHANNELMODEIS		"324"
#define	RPL_NOTOPIC				"331"
#define	RPL_TOPIC				"332"
#define	RPL_INVITING			"341"
#define	RPL_NAMREPLY			"353"
#define	RPL_ENDOFNAMES			"366"

/// ERROR CODES
#define	ERR_NOSUCHNICK			"401"
#define	ERR_NOSUCHCHANNEL		"403"
#define	ERR_CANNOTSENDTOCHAN	"404"
#define	ERR_NORECIPIENT			"411"
#define	ERR_NOTEXTTOSEND		"412"
#define ERR_UNKNOWNCOMMAND		"421"
#define	ERR_NONICKNAMEGIVEN		"431"
#define	ERR_ERRONEUSNICKNAME	"432"
#define	ERR_NICKNAMEINUSE		"433"
#define	ERR_USERNOTINCHANNEL	"441"
#define	ERR_NOTONCHANNEL		"442"
#define	ERR_USERONCHANNEL		"443"
#define	ERR_NOTREGISTERED		"451"
#define	ERR_NEEDMOREPARAMS		"461"
#define	ERR_ALREADYREGISTERED	"462"
#define	ERR_PASSWDMISMATCH		"464"
#define ERR_KEYSET				"467"
#define	ERR_CHANNELISFULL		"471"
#define ERR_UNKNOWNMODE			"472"
#define	ERR_INVITEONLYCHAN		"473"
#define ERR_BANNEDFROMCHAN      "474"
#define	ERR_BADCHANNELKEY		"475"
#define	ERR_CHANOPRIVSNEEDED	"482"
#define ERR_REASONTOOLONG       "501"
#define ERR_TOPICTOOLONG        "502"

// MESSAGE
#define QUIT_MESSAGE			"/QUIT command used.\n"
#define HELP					"!help"

// ==========================================
// STRING MESSAGES (RFC 2812 FORMATS)
// ==========================================
#define RPL_WELCOME_MSG			":Welcome to the IRC Network "	
#define RPL_YOURHOST_MSG		":Your host is "	
#define RPL_CREATED_MSG			":This server was created today"
#define RPL_ENDOFNAMES_MSG		":End of /NAMES list"
#define RPL_NOTOPIC_MSG			":No topic is set"

#define ERR_UNKNOWNCOMMAND_MSG	":Unknown command"
#define ERR_NOTREGISTERED_MSG	":You have not registered"
#define ERR_REGISTERED_MSG		":You may not reregister"
#define ERR_NEEDMOREPARAMS_MSG	":Not enough parameters"
#define ERR_PASSWDMISMATCH_MSG	":Password incorrect"
#define ERR_NONICKNAMEGIVEN_MSG	":No nickname given"
#define ERR_NEUSNICKNAME_MSG	":Erroneous nickname"
#define ERR_NICKNAMEINUSE_MSG	":Nickname is already in use"
#define ERR_NEEDMOREPARAMS_MSG	":Not enough parameters"
#define ERR_NORECIPIENT_MSG		":No recipient given (PRIVMSG)"
#define ERR_NOTEXTTOSEND_MSG	":No text to send"
#define ERR_NOSUCHCHANNEL_MSG	":No such channel"
#define ERR_INVITEONLYCHAN_MSG	":Cannot join channel (+i)"
#define ERR_CHANNELISFULL_MSG	":Cannot join channel (+l)"
#define ERR_BADCHANNELKEY_MSG	":Cannot join channel (+k)"
#define ERR_BANNEDFROMCHAN_MSG	":Cannot join channel"
#define ERR_NOSENDTOCHAN_MSG	":Cannot send to channel"
#define ERR_NOSUCHNICK_MSG		":No such nick"
#define ERR_NOTONCHANNEL_MSG	":You're not on that channel"
#define ERR_NOPRIVSNEEDED_MSG	":You must have channel operator status to do that"
#define ERR_TOPICTOOLONG_MSG	":100 chars TOPIC limit"
#define ERR_NOUSERCHANNEL_MSG	":They aren't on that channel"
#define ERR_UNKNOWNMODE_MSG		":is unknown mode char to me"
#define ERR_REASONTOOLONG_MSG	":Reason message too long. 100 chars max."
#define ERR_USERONCHANNEL_MSG	":is already on channel"


class CommandExecutor
{
	public:
		~CommandExecutor(void);
		CommandExecutor(IRCModel &model);

		void	execute(Client& client, IRCMessage& msg); // Parseo de ejecucion de comandos de IRC

		/// (JM) METODOS DE LLAMADA DESDE SERVER PARA MODIFICAR O GESTIONAR IRC MODEL
		void    onClientConnect(int fd, const std::string &ip);
		void    onClientDisconnect(int fd);
		Client* getClient(int fd); 						// Delega la petición al modelo

	private:
		CommandExecutor(void);

		// ESTADO IRC
		IRCModel		&_state;
		typedef void (CommandExecutor::*CommandHandler)(Client&, IRCMessage&);
		std::map<std::string, CommandHandler> 		_commandMap;

		// === IRC Manejo de comandos ===

		// Setter
		Channel*		setChannel(const std::string &name, Client &client);

		// Utilidades
		bool			isNickNameInUse(const std::string& nickname); 
		void 			cleanupClient(Client* client, const std::string reason, IRCMessage& msg);
		size_t			paramCount(std::vector<std::string> params) const;
		void			broadcast(Channel *channel, IRCMessage& msg, const std::string& message, int exceptFd);
		bool			isValidNickname(const std::string& nickname);
		void 			sendReply(Client& client, IRCMessage& msg, const std::string& reply);
		bool			requiresRegistration(Client& client, const std::string& command);
		void			sendWellcome(Client& client, IRCMessage& msg);
		
		// Registration
		void			cmdPASS(Client& client, IRCMessage& msg);
		void			cmdNICK(Client& client, IRCMessage& msg);
		void			cmdUSER(Client& client, IRCMessage& msg);
		
		// Comandos de los canales.
		void			cmdJOIN(Client& client, IRCMessage& msg);
		void			cmdPRIVMSG(Client& client, IRCMessage& msg);
		void			cmdPART(Client& client, IRCMessage& msg);
		void			cmdTOPIC(Client& client, IRCMessage& msg);
		
		// Comandos de operador
		void			cmdMODE(Client& client, IRCMessage& msg);
		void			cmdKICK(Client& client, IRCMessage& msg);
		void			cmdINVITE(Client& client, IRCMessage& msg);

		// Comandos Generals
		void			cmdPING(Client& client, IRCMessage& msg);
		void			cmdQUIT(Client& client, IRCMessage& msg);
		void			cmdCAP(Client& client, IRCMessage& msg);
		void			cmdWHO(Client& client, IRCMessage& msg);
};
