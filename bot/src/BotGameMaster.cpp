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

std::vector<std::string> split(const std::string & str)
{
	std::vector<std::string> split;
	std::string elem;
	int		start = 0;
	int		end = 0;
	for (size_t i = 0; i < str.size();)
	{
		while (isspace(str[i]) && str[i])
			i++;
		if (str[i] == ':')
		{
			start = i + 1;
			end = str.size();
			split.push_back(str.substr(start, end - start));
			return split;
		}
		else
		{
			start = i;
			while (!isspace(str[i]) && str[i])
				i++;
			end = i;
			split.push_back(str.substr(start, end - start));
		}
	}
	return split;
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

void	BotGameMaster::connectServer()
{
	bool	running = true;
	int		recv_bytes;
	
	if (connect(_botFd, _servInfo->ai_addr, _servInfo->ai_addrlen) < 0)
	{
		freeaddrinfo(_servInfo);
		close(_botFd);
		std::cout << "connect failed en fait c tro grav" << std::endl;
		return ;
	}
	authentication();
	createRooms();
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
			parsePlayerCmd(buf);
	}
}

std::string	BotGameMaster::parsePlayerNick(std::string content)
{
	std::string result;
	size_t del = content.find("!");

	result = content.substr(0, del);
	result.erase(result.begin());
	return (result);
}

std::string	BotGameMaster::getMessage(std::vector<std::string> args)
{
	size_t pos = args.size() - 1;

	return (args[pos]);
}


bool BotGameMaster::isPrivMsg(std::vector<std::string> args)
{
	if (args.size() > 1)
		return (args[1] == "PRIVMSG");
	return (false);
}

std::vector<std::string>	BotGameMaster::getArgs(std::string str)
{
	std::vector<std::string> args;

	str.erase(str.begin());
	args = split(str);
	return (args);	
}

bool BotGameMaster::isGameCmd(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isspace(str[i]))
		{
			if (str[i] == '*')
				return (true);
		}
	}
	return (false);
}

std::string BotGameMaster::extractGameCmd(std::string str)
{
	std::vector<std::string> splitted = split(str);

	splitted[0].erase(splitted[0].begin());
	for (size_t i = 0; i < splitted[0].length(); i++)
	{
		splitted[0][i] = toupper(splitted[0][i]);
	}
	return (splitted[0]);
}

void	BotGameMaster::parsePlayerCmd(char *str)
{
	t_parse parse;

	parse.player = parsePlayerNick(str);
	parse.args = getArgs(str);
	if (!isPrivMsg(parse.args))
		return ;
	parse.content = getMessage(parse.args);
	if (parse.content.size() > 0)
	{
		if (isGameCmd(parse.content))
		{
			parse.cmd = extractGameCmd(parse.content);
			parse.msg = "PRIVMSG " + parse.player + " :GameCommand received\r\n";
			sendCommand(parse.msg);
			manageGameCommand(parse.player, parse.cmd);
		}
		else
		{
			parse.msg = "PRIVMSG " + parse.player + " :Kechia ?\r\n";
			sendCommand(parse.msg);
		}
	}
}

void	BotGameMaster::sendCommand(std::string msg)
{
	send(_botFd, msg.c_str(), msg.length(), 0);
}

void    BotGameMaster::setupPlayers(std::string command)
{
    int pos = command.find(":");
    std::vector<std::string> playerList = split(command.substr(pos + 1));

    for (size_t i = 0; i < playerList.size(); i++)
    {
        _players[playerList[i]] = (e_roomId)1;
    }
}
