#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

class BotGameMaster 
{
	public :
		BotGameMaster();
		~BotGameMaster();
		void				initBot();

	private :
		struct addrinfo		*_servInfo;
		std::string			_pass;
		std::string			_servPort;
		int					_servFd;

};

