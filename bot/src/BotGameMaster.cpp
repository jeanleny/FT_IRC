#include <BotGameMaster.hpp>

BotGameMaster::BotGameMaster()
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
	if (getaddrinfo(NULL, _servPort.c_str(), &servParam, &_servInfo) != 0)
	{
		std::cout << "getaddrinfo failed" << std::endl;
		return ;
	}
	_servFd = socket(_servInfo->ai_family, _servInfo->ai_socktype, _servInfo->ai_protocol);
	if (_servFd == -1)
	{
		freeaddrinfo(_servInfo);
		std::cout << "socket Failed" << std::endl;
		return ;
	}
	if (bind(_servFd, _servInfo->ai_addr, _servInfo->ai_addrlen) == -1)
	{
		freeaddrinfo(_servInfo);
		close(_servFd);
		std::cout << "bind Failed" << std::endl;
	}
	if (listen(_servFd, 10) == -1)
	{
		freeaddrinfo(_servInfo);
		close(_servFd);
		std::cout << "listen failed" << std::endl;
	}
}

