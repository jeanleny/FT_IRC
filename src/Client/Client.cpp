#include <Client.hpp>

int	Client::getClientFd() const
{
	return (_clientFd);
}

std::string		Client::getNickname() const
{
	return (_nickname);
}

std::string		Client::getUsername() const
{
	return (_username);
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

void	Client::setNickname(std::string nick)
{
	_nickname = nick;
}

void	Client::setUsername(std::string username)
{
	_username = username;
}


void	Client::clearCommandArgs()
{
	_commandArgs.clear();
}

Client::Client(int fd) : _clientFd(fd), _registerStatus(PASS_STATUS), _nickname("")
{

};

Client::~Client(){};

