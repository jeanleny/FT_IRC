#include <BotGameMaster.hpp>

BotGameMaster::BotGameMaster(char *port, char *pass) : _servPort(port), _pass(pass), _gameRunning(false)
{
	_rooms.push_back("#TAVERN");
	_rooms.push_back("#CORRIDOR");
	_rooms.push_back("#ROOM");

	_topics.push_back("**Welcome to the Tavern ! Please take a sit, and when all the daring adventurers are present, enter the command START**");
	_topics.push_back("**A dark corridor leading to a closed door.**");
	_topics.push_back("**A forgotten and enigmatic room in the depths of a dungeon.**");

	std::vector<std::string> tavern;
	tavern.push_back("START");
	std::vector<std::string> corridor;
	corridor.push_back("WALL");
	corridor.push_back("SKELETON");
	corridor.push_back("DOOR");
	corridor.push_back("LEVER");
	std::vector<std::string> room;
	//room.push_back();
	_gameCmd[TAVERN] = tavern;
	_gameCmd[CORRIDOR] = corridor;
	_gameCmd[ROOM] = room;
}

BotGameMaster::~BotGameMaster()
{

}

void	BotGameMaster::initBot()
{
	struct addrinfo servParam;
	
	memset(&servParam, 0, sizeof(servParam));

	servParam.ai_family = AF_UNSPEC;
	servParam.ai_socktype = SOCK_STREAM;
	servParam.ai_flags = AI_PASSIVE;
	gethostname(_hostName, sizeof(_hostName));
	if (getaddrinfo(_hostName, _servPort.c_str(), &servParam, &_servInfo) != 0)
	{
		std::cout << "getaddrinfo failed" << std::endl;
		return ;
	}
	_botFd = socket(_servInfo->ai_family, _servInfo->ai_socktype, _servInfo->ai_protocol);
	if (_botFd == -1)
	{
		freeaddrinfo(_servInfo);
		std::cout << "socket Failed" << std::endl;
		return ;
	}
}

void	BotGameMaster::createRooms()
{
	for(size_t i = 0; i < _rooms.size(); i++)
	{
		sendCommand("JOIN " + _rooms[i] + "\r\n");
		usleep(100000);
		sendCommand("TOPIC " + _rooms[i] + " :" + _topics[i] + "\r\n");
		usleep(100000);
		if (i != 0)
			sendCommand("MODE " + _rooms[i] + " +i" + "\r\n");
		usleep(100000);
	}
}

void	BotGameMaster::authentication()
{
	sendCommand("PASS " + _pass + "\r\n");
	usleep(100000);
	sendCommand("USER Master\r\n");
	usleep(100000);
	sendCommand("NICK Master\r\n");
	usleep(100000);
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

