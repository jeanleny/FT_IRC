#include "Server.hpp"
#include <sstream>

Server*	Server::_instance = NULL;

Server& Server::getInstance()
{
	return (*_instance);
}

std::vector<std::string> split(const std::string & str)
{
   std::vector<std::string> split;
   std::string elem;
   int		start = 0;
   int		end = 0;
   for (size_t i = 0; i < str.size();)
   {
		while (isspace(str[i]))
			i++;
		start = i;
		while (!isspace(str[i]))
			i++;
		end = i;
		split.push_back(str.substr(start, end - start));
   }
   return split;
}

Server::Server(char *port, char *password)
{
	if (_instance == NULL)
	{
		_instance = this;
		_servPort = port;
		_password = password;
		gethostname(_hostName, sizeof(_hostName));
	}
}

void	Server::initICommands()
{
	_iCommands[0] = new PassCommand();
	_iCommands[1] = NULL;
	_iCommands[2] = NULL;
	_iCommands[3] = NULL;
	_iCommands[4] = NULL;
	_iCommands[5] = NULL;
	_iCommands[6] = NULL;
	_iCommands[7] = NULL;
	_iCommands[8] = NULL;
}

void	Server::initServer()
{
	struct addrinfo	servParam;

	memset(&servParam, 0, sizeof(servParam));
	servParam.ai_family = AF_UNSPEC;
	servParam.ai_socktype = SOCK_STREAM;
	servParam.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, _servPort.c_str(), &servParam, &_servInfo) != 0)
		throw AddrinfoFailedException();
	_servFd = socket(_servInfo->ai_family, _servInfo->ai_socktype, _servInfo->ai_protocol);
	if (_servFd == -1)
		throw SocketFailedException();
	if (bind(_servFd, _servInfo->ai_addr, _servInfo->ai_addrlen) == -1)
		throw BindFailedException();
	if (listen(_servFd, 10) == -1)
		throw ListenFailedException();
	
	initICommands();
}

void	Server::initEpoll()
{
	_epollFd = epoll_create1(0);
	_userEvents.events = EPOLLIN;
	_userEvents.data.fd = _servFd;
	epoll_ctl(_epollFd, EPOLL_CTL_ADD, _servFd, &_userEvents);
}

void	Server::addClient()
{
	struct	sockaddr_storage	emitter;
	socklen_t					addrSize;
	int							emitterFd;

	addrSize = sizeof (struct sockaddr);
	emitterFd = accept(_servFd, (struct sockaddr *)&emitter, &addrSize);
	Client	obj(emitterFd);
	_clients.push_back(obj);
	_userEvents.events = EPOLLIN;
	_userEvents.data.fd = emitterFd;
	epoll_ctl(_epollFd, EPOLL_CTL_ADD, emitterFd, &_userEvents);
}

ssize_t	Server::findClient(int clientFd)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (clientFd == _clients[i].getClientFd())
			return (i);
	}
	return (-1);
}

void	displayClients(std::vector<Client> _clients)
{
	for(size_t i = 0; i < _clients.size(); i++)
	{
		std::cout << _clients[i].getClientFd() << std::endl;
	}
}

void	Server::manageWrongEvents(int bytes, ssize_t removeIndex, int eventFd)
{
	if (bytes < 0)
		throw RecvFailedException();
	std::cout << "User disconnected from the server" << std::endl;
	epoll_ctl(_epollFd, EPOLL_CTL_DEL, eventFd, &_userEvents);
	removeIndex = findClient(eventFd);
	if (removeIndex < 0)
		return ;
	_clients.erase(_clients.begin() + removeIndex);
}

bool	isRegisterCommand(ssize_t cmdId)
{
	if (cmdId == USER || cmdId == NICK || cmdId == PASS)
		return (true);
	return (false);
}

void	Server::serverRegistration(Client & client)
{
	int status = client.getRegisterStatus();
	size_t cmdId = client.getCommandId();

	if (!isRegisterCommand(cmdId))
		throw RegisterQueryException();
	switch (status)
	{
		case PASS_STATUS :
			if (cmdId != PASS)
				std::cout << "Please enter the password" << std::endl; //send
			else
				_iCommands[PASS]->execCmd(client, client.getCommandArgs());
			break ;	
		case USER_STATUS :
			if (cmdId != USER)
				std::cout << "Please enter your username" << std::endl; //send
			//else
			//USER COMAND
			break ;
		case NICK_STATUS :
			if (cmdId != NICK)
				std::cout << "Please enter your nickname" << std::endl; //send
			//else
			//NICK COMAND
			break ;
	}
}

bool	Server::validPassword(std::string pass)
{
	return (pass == _password);
}

void	Server::commandSwitch(Client & client)
{
	size_t	commandId = client.getCommandId();

	//_iCommands[commandId].execCmd();

	switch (commandId)
	{
		case PASS:
			//--> PASS COMMAND
			break;
	
		case NICK:
			//--> NICK COMMAND
			break;

		case USER:
			//--> USER COMMAND
			break;
	
		case KICK:
			//--> KICK COMMAND
			break;

		case PRIVMSG:
			//--> PRIVMSG COMMAND
			break;
	
		case TOPIC:
			//--> TOPIC COMMAND
			break;

		case MODE:
			//--> MODE COMMAND
			break;
	
		case JOIN:
			//--> JOIN COMMAND
			break;	

		case INVITE:
			//--> INVITE COMMAND
			break;
	
		case UNKNOWN:
			std::cerr << "Unvalid command." << std::endl; //send
			break;
	}
}

void	Server::manageCommand(int recvBytes, Client & client)
{
	(void)recvBytes;
	
	if (client.getRegisterStatus() != REGISTERED)
	{
		try
		{
			serverRegistration(client);
		}
		catch (const std::exception & e)
		{
			std::cerr << e.what() << std::endl; //send
		}
	}
	else
	{
		try
		{
			commandSwitch(client);
		}
		catch(const std::exception & e)
		{
			std::cerr << e.what() << std::endl; //send
		}
	}
}


bool isOneArg(std::string str)
{
	int	i = 0;
	while (isspace(str[i]) && str[i])
		i++;
	while (!isspace(str[i]) && str[i])
		i++;
	while (isspace(str[i]) && str[i])
		i++;
	return (str[i] == '\0');
}

void	Server::extractCommandId(Client & emitter, std::string id)
{
	std::string array[NB_CMD]= {"PASS", "NICK", "USER", "KICK", "PRIVMSG", "TOPIC", "MODE", "JOIN", "INVITE"};
	for (size_t i = 0; i < NB_CMD; i++)
	{
		if (id == array[i])
		{
			emitter.setCommandId(i);
			return ;
		}
	}
	emitter.setCommandId(UNKNOWN);
}

void	Server::extractCommand(char *buf, Client & client)
{
	std::string	extract;
	std::string	str = buf;
	str.erase(str.size() - 2, str.size() - 1);
	if (isOneArg(str))
		extractCommandId(client, str);
	else
	{
		std::vector<std::string>	splitArgs = split(str);
		extractCommandId(client, splitArgs[0]);
		splitArgs.erase(splitArgs.begin());
		client.setCommandArgs(splitArgs);
	}
}


void	Server::manageEvents(struct epoll_event currentEvent)
{
	char buf[1024];
	int recvBytes = recv(currentEvent.data.fd, buf, 1023, 0);
	ssize_t	clientIndex = findClient(currentEvent.data.fd);
	if (recvBytes <= 0)
	{
		try
		{
			manageWrongEvents(recvBytes, clientIndex, currentEvent.data.fd);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl; //send
		}
	}
	else if (recvBytes > 0)
	{
		buf[recvBytes] = '\0';
		try
		{
			extractCommand(buf, _clients[clientIndex]);
			manageCommand(recvBytes, _clients[clientIndex]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl; //send
		}
	}
}

void	Server::runningServer()
{
	int	newConnections;
	initEpoll();
	
	while (1)
	{
		newConnections = epoll_wait(_epollFd, _queuedEvents, MAX_EVENTS, -1);
		for (int i = 0; i < newConnections; i++)
		{
			if (_queuedEvents[i].events & EPOLLIN)
			{
				if (_queuedEvents[i].data.fd == _servFd)
					addClient();
				else
					manageEvents(_queuedEvents[i]);
			}
		}
	}
}

Server::~Server()
{
	for (int i = 0; i < NB_CMD; i++)
	{
		delete _iCommands[i];
	}
	_instance = NULL;
};
