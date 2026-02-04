#include <ModeCommand.hpp>

ModeCommand::ModeCommand()
{

}

ModeCommand::~ModeCommand()
{

}

bool	validModeFlag(char a)
{
	if (a == 't' || a == 'i' || a == 'k' || a == 'o' || a == 'l')
		return (true);
	return (false);
}

bool	isAddSub(char a, bool & disable)
{
	if (a == '-' || a == '+')
	{
		if (a == '-')
			disable = true;
		return (true);
	}
	return (false);
}

void	sendModeError(Client client, char arg)
{
	std::string msg = ":" + Server::getInstance().getHostname() + " 472 " + client.getNickname() + arg + ":is not a recognised channel mode.\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

void	sendDigitError(Client client, std::string arg)
{
	std::string msg = ":" + Server::getInstance().getHostname() + " 696 " + client.getNickname() + arg + " :Invalid limit mode parameter.\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

bool	paramFlag(char flag)
{
	return (flag == 'o' || flag == 'k' || flag == 'l');
}

void	ModeCommand::addFlags(Client emitter, std::string arg)
{
	for (size_t i = 0; i < arg.size(); i++)
	{
		if (isAddSub(arg[i], _disable))
			i++;
		if (!validModeFlag(arg[i]))
		{
			sendModeError(emitter, arg[i]);
			continue ;
		}
		else
			_flags += arg[i];
	}
}

size_t	selectMode(char a)
{
	const char array[MODE_NB] = {'t', 'i', 'k', 'o', 'l'};

	for (int i = 0; i < MODE_NB; i++)
	{
		if (a == array[i])
			return (i);
	}
	return (-1);
}

void	ModeCommand::addSendArgs()
{
	_sendArgs += " ";
	if (_id == _paramArg.size())
		_sendArgs += ":";
	_sendArgs += _paramArg[_id];
	_id++;
}

bool	ModeCommand::manageLimitMode(Client client)
{
	if (!_disable && _paramArg.size() > 0)
	{
		if (!strIsDigit(_paramArg[_id]))
		{
			sendDigitError(client, _paramArg[_id]);
			return (false);
		}
		Server::getInstance().changeChannelLimit(_chanName, atoi(_paramArg[_id].c_str()));
		addSendArgs();
		return (true);
	}
	else if (_disable)
		return (true);
	return (false);
}

bool	ModeCommand::manageKeyMode()
{
	if (_disable)
	{
		Server::getInstance().changeChannelKey(_chanName, "");
		return (true);
	}
	addSendArgs();
	Server::getInstance().changeChannelKey(_chanName, _paramArg[_id]);
	return (true);
}

bool	ModeCommand::manageParamMode(char flag, int fd)
{
	if (!paramFlag(flag))
		return (true);
	if (flag == 'l')
		return (manageLimitMode(fd));
	if (flag == 'k')
		return (manageKeyMode());
	return (false);
}

void	ModeCommand::sendModeMessage(Client client)
{
	std::string msg = ":" + client.getNickname() + "!" + client.getUsername() + Server::getInstance().getHostname() + " MODE " + _chanName + _sign + _param;
	if (_paramArg.size() > 0)
		msg += " " + _sendArgs + "\r\n";
	else
		msg += "\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

void	ModeCommand::modeParam(Client client)
{
	for (size_t i = 0; i < _flags.size(); i++)
	{
		_mode = selectMode(_flags[i]);
		if (Server::getInstance().checkChannelMode(_chanName, _mode ,_disable))
		{
			if (manageParamMode(_flags[i], client.getClientFd()))
			{
				Server::getInstance().changeChannelMode(_chanName, _mode ,_disable);
				_param += _flags[i];
			}
		}
	}
	if (_param.size() > 0)
		sendModeMessage(client);
}

void	ModeCommand::initMode(Client emitter, std::vector<std::string> args)
{
	_sendArgs = "";
	_param = "";
	_flags = "";
	_disable = false;
	_sign = " :+";
	_chanName = args[0];
	_paramArg = args;
	_paramArg.erase(_paramArg.begin() , _paramArg.begin() + 2);
	_id = 0;
	addFlags(emitter, args[1]);
	if (_disable)
		_sign = " :-";
}

void	ModeCommand::execCmd(Client &emitter, const std::vector<std::string>& arg)
{
	if (arg.size() < 1)
		throw NotEnoughParametersException(emitter);
	if (!checkPrefix(arg[0]))
		throw InvalidChannelException(emitter);
	if (!Server::getInstance().existChannel(arg[0]))
		throw NoSuchChannelException(emitter);
	if (arg.size() == 1)
	  Server::getInstance().displayChannelMode(emitter, arg[0]);
	else
	{
		initMode(emitter, arg);
		if (_flags.size() > 0)
			modeParam(emitter);
	}
}
