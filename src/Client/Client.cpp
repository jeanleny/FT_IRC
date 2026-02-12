#include <Client.hpp>
#include <utils.h>

int	Client::getClientFd() const
{
	return (_clientFd);
}

std::string		Client::getNickname() const
{
	return (_nickname);
}

std::string		Client::getOldNickname() const
{
	return (_oldNickname);
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

std::string Client::getCmd() const
{
	return(_cmd);
}

std::string	Client::getBuf() const
{
	std::string str = _buf;
	std::memset((char *)_buf, 0, sizeof(_buf));
	return(str);
}

std::vector<std::string>	Client::getCommandArgs() const
{
	return (_commandArgs);
}

void Client::setCommandId(size_t id)
{
	_commandId = id;
}

void Client::setCmd(std::string arg)
{
	_cmd = arg;
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
	_oldNickname = _nickname;
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

int	Client::storeInBuf(char *buf)
{
	int i = 0;
	int j = strlen(_buf);
	while (buf[i] && j < 1024)
	{
		_buf[j] = buf[i];
		i++;
		j++;
	}
	if (isCtrlD(buf))
		return -1;
	return 0;
}

Client::Client(int fd) : _clientFd(fd), _registerStatus(PASS_STATUS), _nickname("*"), _oldNickname("*")
{
	std::memset(_buf, 0, sizeof(_buf));
};

Client::~Client(){};

