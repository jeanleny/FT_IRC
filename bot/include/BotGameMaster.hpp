#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

typedef struct s_parse
{
	std::vector<std::string> args;
	std::string	content;
	std::string	player;
	std::string	cmd;
	std::string	msg;
} t_parse;

class BotGameMaster 
{
	public :
		BotGameMaster(char *port, char *pass);
		~BotGameMaster();
		void						initBot();
		void						connectServer();
		void						sendCommand(std::string msg);
		std::string					parsePlayerNick(std::string content);
		std::string					getMessage(std::vector<std::string> args);
		std::string					extractGameCmd(std::string str);
		std::vector<std::string>	getArgs(std::string str);
		bool						isPrivMsg(std::vector<std::string> args);
		bool						isGameCmd(std::string str);
		void						parsePlayerCmd(char *str);

	private :
		struct addrinfo			*_servInfo;
		std::string				_servPort;
		std::string				_pass;
		int						_botFd;
		char					_hostName[128];
};
void		parsePlayerCmd(char *str);

