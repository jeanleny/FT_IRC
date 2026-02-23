#include <BotGameMaster.hpp>


BotGameMaster::BotGameMaster(char *port, char *pass) : _servPort(port), _pass(pass), _gameRunning(false)
{
	createRoomsName();
	createTopics();
	createLibrary();
	createMessages();
}

BotGameMaster::~BotGameMaster()
{
}


void	BotGameMaster::createRooms()
{
	for(size_t i = 0; i < _rooms.size(); i++)
	{
		sendCommand("JOIN " + _rooms[i] + "\r\n");
		sendCommand("TOPIC " + _rooms[i] + " :" + _topics[i] + "\r\n");
		if (i != 0)
			sendCommand("MODE " + _rooms[i] + " +i" + "\r\n");
	}
}

void	BotGameMaster::authentication()
{
	sendCommand("PASS " + _pass + "\r\n");
	sendCommand("NICK Master\r\n");
	sendCommand("USER Master\r\n");
}

int	BotGameMaster::servConnect()
{
	if (connect(_botFd, _servInfo->ai_addr, _servInfo->ai_addrlen) < 0)
	{
		freeaddrinfo(_servInfo);
		close(_botFd);
		std::cout << "connect failed en fait c tro grav" << std::endl;
		return (-1);
	}
	return (0);
}

void	BotGameMaster::servProcess()
{
	std::vector<std::string> array;
	bool	running = true;
	int		recv_bytes;

	while (running)
	{
		char 	buf[1024];
		recv_bytes = recv(_botFd, &buf, 1023, 0);
		buf[recv_bytes] = '\0';
		if (recv_bytes <= 0)
		{
			freeaddrinfo(_servInfo);
			close(_botFd);
			std::cout << "Server Connection's lost" << std::endl;
			return ;
		}
		else if (recv_bytes > 0)
		{
			array = trailingSplit(buf);	
			for (size_t i = 0; i < array.size(); i++)
			{
				t_parse parse;
				parsePlayerCmd(array[i], &parse);
				if (parse.valid)
					manageGameCommand(parse);
			}
		}
	}
}

void	BotGameMaster::botConnect()
{
	
	if (servConnect() < 0)
		return ;
	authentication();
	createRooms();
	servProcess();
}


void	BotGameMaster::sendCommand(std::string msg)
{
	send(_botFd, msg.c_str(), msg.length(), 0);
}

