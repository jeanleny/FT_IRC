#include "Server.hpp"

Server::Server(char *port, char *password)
{
	_servPort = port;
	_password = password;
	gethostname(_hostName, sizeof(_hostName));
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

void	Server::manageWrongEvents(int bytes, int eventFd)
{
	ssize_t removeIndex;
	if (bytes < 0)
		throw RecvFailedException();
	std::cout << "User disconnected from the server" << std::endl;
	epoll_ctl(_epollFd, EPOLL_CTL_DEL, eventFd, &_userEvents);
	removeIndex = findClient(eventFd);
	if (removeIndex < 0)
		return ;
	_clients.erase(_clients.begin() + removeIndex);
}

void	Server::manageEvents(struct epoll_event currentEvent)
{
	char buf[1024];
	int recvBytes = recv(currentEvent.data.fd, buf, 1023, 0);
	if (recvBytes <= 0)
	{
		try
		{
			manageWrongEvents(recvBytes, currentEvent.data.fd);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
	}
	}
	else if (recvBytes > 0)
	{
		buf[recvBytes] = '\0';
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
