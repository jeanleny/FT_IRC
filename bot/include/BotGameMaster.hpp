#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_parse
{
	std::string	content;
	std::string	Player;
	
} t_parse;

class BotGameMaster 
{
	public :
		BotGameMaster(char *port, char *pass);
		~BotGameMaster();
		void				initBot();
		void				connectServer();
		void				sendCommand(std::string msg);

	private :
		struct addrinfo			*_servInfo;
		std::string				_servPort;
		std::string				_pass;
		int						_botFd;
		char					_hostName[128];

};
void		parsePlayerCmd(char *str);
std::string	parsePlayerNick(std::string content);

