#include <BotGameMaster.hpp>

BotGameMaster::BotGameMaster(char *port, char *pass) : _servPort(port), _pass(pass)
{

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
	sendCommand("PASS " + _pass + "\r\n");
	usleep(100000);
	sendCommand("USER Master \r\n");
	usleep(100000);
	sendCommand("NICK Master \r\n");
	while (running)
	{
		char 	buf[1024];
		recv_bytes = recv(_botFd, buf, sizeof(buf), 0);
		buf[recv_bytes] = '\0';
		if (recv_bytes == 0)
		{
			freeaddrinfo(_servInfo);
			close(_botFd);
			std::cout << "Server Connection's lost" << std::endl;
			return ;
		}
		std::cout << buf << std::endl;
		parsePlayerCmd(buf);
	}
}

std::string	parsePlayerNick(std::string content)
{
	std::string result;
	size_t del = content.find("!");

	result = content.substr(0, del);
	result.erase(result.begin());
	return (result);
}

void	parsePlayerCmd(char *str)
{
	t_parse parse;
	parse.content = str;
	parse.Player = parsePlayerNick(parse.content);
}

void	BotGameMaster::sendCommand(std::string msg)
{
	send(_botFd, msg.c_str(), msg.length(), 0);
}
