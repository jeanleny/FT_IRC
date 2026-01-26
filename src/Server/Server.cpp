#include "Server.hpp"

Server*	Server::_instance = NULL;

void	Server::poussememe()
{
	std::cout << "manger du celeri" << std::endl;
}

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

void	Server::initICommands()
{
	// _iCommands[0] = new PassCommand();
	// _iCommands[1] = new UserCommand();
	// _iCommands[2] = new NickCommand();
	// _iCommands[3] = new KickCommand();
	// _iCommands[4] = new PrivMsgCommand();
	// _iCommands[5] = new TopicCommand();
	// _iCommands[6] = new ModeCommand();
	// _iCommands[7] = new JoinCommand();
	// _iCommands[8] = new InviteCommand();
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
	std::cout << cmdId << std::endl;
	if (cmdId == USER || cmdId == NICK || cmdId == PASS)
		return (true);
	return (false);
}

void	Server::serverRegistration(int index)
{
	int status = _clients[index].getRegisterStatus();
	size_t cmdId = _clients[index].getCommandId();

	if (!isRegisterCommand(cmdId))
		throw RegisterQueryException();
	switch (status)
	{
		case PASS_STATUS :
			if (cmdId != PASS)
				std::cout << "Please enter the password" << std::endl;
			//else
			//PASS COMAND
			break ;	
		case USER_STATUS :
			if (cmdId != USER)
				std::cout << "Please enter your username" << std::endl;
			//else
			//USER COMAND
			break ;
		case NICK_STATUS :
			if (cmdId != NICK)
				std::cout << "Please enter your nickname" << std::endl;
			//else
			//NICK COMAND
			break ;
	}
}
void	Server::commandSwitch(int clientIndex)
{
	size_t	commandId = _clients[clientIndex].getCommandId();

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
			std::cerr << "Unvalid command." << std::endl;
			//-->fonction send
			break;
	}
}

void	Server::manageCommand(int recvBytes, ssize_t index)
{
	(void)recvBytes;
	
	if (_clients[index].getRegisterStatus() != REGISTERED)
	{
		try
		{
			serverRegistration(index);
		}
		catch (const std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else
	{
		try
		{
			commandSwitch(index);
		}
		catch(const std::exception & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}



void	Server::extractCommandId(char *buf, int clientIndex)
{
	std::string	extract;
	std::string	str = buf;
	str.erase(str.size() - 2, str.size() - 1);
	size_t	pos = str.find(" ");
	if (pos == str.npos)
		extract = str;
	else
	{
		extract = str.substr(0, pos);
		std::string	arg = str.substr(pos);
		_clients[clientIndex].setCommandArg(arg);
	}

	std::string array[9]= {"PASS", "NICK", "USER", "KICK", "PRIVMSG", "TOPIC", "MODE", "JOIN", "INVITE"};

	for (size_t i = 0; i < 9; i++)
	{
		if (extract == array[i])
		{
			_clients[clientIndex].setCommandId(i);
			return ;
		}
	}
	_clients[clientIndex].setCommandId(UNKNOWN);
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
			std::cerr << e.what() << std::endl;
		}
	}
	else if (recvBytes > 0)
	{
		buf[recvBytes] = '\0';
		try
		{
			extractCommandId(buf, clientIndex);
			manageCommand(recvBytes, clientIndex);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
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

Server::~Server(){};
