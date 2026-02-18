#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <vector>

class BotGameMaster 
{
	public :
		BotGameMaster(char *port, char *pass);
		~BotGameMaster();
		void				initBot();
		void				connectServer();
		void				sendCommand(std::string msg);
		void				authentication();
		void				createRooms();

	private :
		struct addrinfo				*_servInfo;
		std::string					_servPort;
		std::string					_pass;
		int							_botFd;
		char						_hostName[128];
		std::vector<std::string>	_rooms;
		std::vector<std::string>	_topics;
};

