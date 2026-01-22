#include "Client.hpp"

int	Client::getClientFd()
{
	return (_clientFd);
}

Client::Client(int fd) : _clientFd(fd)
{

};

Client::~Client(){};
