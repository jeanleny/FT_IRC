#include "Client.hpp"

int	Client::getClientFd() const
{
	return (_clientFd);
}

int	Client::getRegisterStatus() const
{
	return (_registerStatus);
}

size_t Client::getCommandId() const
{
	return (_commandId);
}

std::string	Client::getCommandArg() const
{
	return (_commandArg);
}

void Client::setCommandId(size_t id)
{
	_commandId = id;
}

void Client::setCommandArg(std::string arg)
{
	_commandArg = arg;
}

Client::Client(int fd) : _clientFd(fd), _registerStatus(PASS_STATUS)
{

};

Client::~Client(){};
