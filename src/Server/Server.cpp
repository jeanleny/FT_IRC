#include <Server.hpp>

Server*	Server::_instance = NULL;

Server& Server::getInstance()
{
	return (*_instance);
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

std::string	Server::getHostname() const
{
	return ((std::string)_hostName);
}

void	Server::initICommands()
{
	_iCommands[0] = new PassCommand();
	_iCommands[1] = new UserCommand();
	_iCommands[2] = new NickCommand();
	_iCommands[3] = new KickCommand();
	_iCommands[4] = new PrivmsgCommand();
	_iCommands[5] = new TopicCommand();
	_iCommands[6] = new ModeCommand();
	_iCommands[7] = new JoinCommand();
	_iCommands[8] = new InviteCommand();
	_iCommands[9] = new PartCommand();
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
	int	opt = 1;
	setsockopt(_servFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (bind(_servFd, _servInfo->ai_addr, _servInfo->ai_addrlen) == -1)
	{
		close(_servFd);
		throw BindFailedException();
	}
	if (listen(_servFd, 10) == -1)
	{
		close(_servFd);
		throw ListenFailedException();
	}
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
	_clientsFds.push_back(emitterFd);
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

Client	Server::getClientByNickname(std::string nickname) const
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getNickname() == nickname)
			return _clients[i];
	}
	Client	null(-1);
	return null;
}

void	Server::clearWrongEvent(size_t rmIndex)
{
	std::string	chanName;

	for (size_t i = 0; i < _channels.size(); i++)
	{
		chanName = _channels[i].getName();
		_clients[rmIndex].setCommandId(PRIVMSG);
		if (isInChannel(_clients[rmIndex], chanName))
			removeChannelMember(_clients[rmIndex], chanName);
	}
}


void	Server::manageWrongEvents(int bytes, ssize_t rmIndex, int eventFd)
{	
	if (bytes < 0)
		throw RecvFailedException();
	std::cout << "User disconnected from the server" << std::endl;
	rmIndex = findClient(eventFd);
	if (rmIndex < 0)
		return ;
	clearWrongEvent(rmIndex);
	close(_clients[rmIndex].getClientFd());
	_clients.erase(_clients.begin() + rmIndex);
	epoll_ctl(_epollFd, EPOLL_CTL_DEL, eventFd, &_userEvents);
}

void	Server::serverRegistration(Client & client)
{
	int status = client.getRegisterStatus();
	size_t cmdId = client.getCommandId();
	std::vector<std::string> cmdArgs = client.getCommandArgs();
	switch (status)
	{
		case PASS_STATUS :
			if (cmdId != PASS)
				throw CustomErrorException(client);
			_iCommands[PASS]->execCmd(client, cmdArgs);
			break ;
		case USER_STATUS :
			if (cmdId != USER)
				throw CustomErrorException(client);
			_iCommands[USER]->execCmd(client, cmdArgs);
			break ;
		case NICK_STATUS :
			if (cmdId != NICK)
				throw CustomErrorException(client);
			_iCommands[NICK]->execCmd(client, cmdArgs);
			break ;
	}
}

bool	Server::isUsedNickname(std::string nickname)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (nickname == _clients[i].getNickname())
			return true;
	}
	return false;
}

bool	Server::validPassword(std::string pass)
{
	return (pass == _password);
}

void	Server::manageCommand(int recvBytes, Client & client)
{
	(void)recvBytes;
	
	if (client.getRegisterStatus() != REGISTERED)
			serverRegistration(client);
	else
	{
		size_t	commandId = client.getCommandId();
		std::vector<std::string> cmdArgs = client.getCommandArgs();
		if (commandId == UNKNOWN)
		{
			throw UnknownCommandException(client);
		}
		_iCommands[commandId]->execCmd(client, cmdArgs);
	}
}

void	Server::extractCommandId(Client & emitter, std::string id)
{
	uppercaseStr(id);
	const std::string array[NB_CMD]= {"PASS", "USER", "NICK", "KICK", "PRIVMSG", "TOPIC", "MODE", "JOIN", "INVITE", "PART"};
	emitter.setCmd(id);
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

int	Server::extractCommand(char *buf, Client & client)
{
	std::string	extract;
	std::string	str = buf;
	if (isEmptyCommand(str))
		return (ERROR);
	eraseTrailingSpaces(str);
	if (isOneArg(str))
		extractCommandId(client, str);
	else
	{
		std::vector<std::string>	splitArgs = split(str);
		extractCommandId(client, splitArgs[0]);
		splitArgs.erase(splitArgs.begin());
		client.setCommandArgs(splitArgs);
	}
	return (1);
}

void	Server::manageEvents(struct epoll_event &currentEvent)
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
			std::cerr << "Wrong Event Happened" << std::endl;
		}
	}
	else if (recvBytes > 0)
	{
		buf[recvBytes] = '\0';
		if (extractCommand(buf, _clients[clientIndex]) < 0)
			return ;
		try
		{
			manageCommand(recvBytes, _clients[clientIndex]);
		}
		catch(const std::exception& e)
		{
			sendException(currentEvent.data.fd, e);
		}
	}
	_clients[clientIndex].clearCommandArgs();
}

void	Server::runningServer()
{
	int	newConnections;
	initEpoll();
	setSigaction();
	while (!g_exit)
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
	serverClosing();
	freeaddrinfo(_servInfo);
}

Server::~Server()
{
	for (int i = 0; i < NB_CMD; i++)
	{
		delete _iCommands[i];
	}
	_instance = NULL;
};
