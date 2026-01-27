#include <Client.hpp>

Client::Client(int fd) : _clientFd(fd), _registerStatus(PASS_STATUS)
{

};

Client::~Client(){};

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

std::vector<std::string>	Client::getCommandArgs() const
{
	return (_commandArgs);
}

void Client::setCommandId(size_t id)
{
	_commandId = id;
}

void Client::setCommandArgs(std::vector<std::string> args)
{
	_commandArgs = args;
}

void	Client::setRegisterStatus(int status)
{
	_registerStatus = status;
}


