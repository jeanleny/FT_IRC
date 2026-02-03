#include <Channel.hpp>
#include <Server.hpp>

Channel::Channel(std::string name) : _name(name), _memberNb(0), _memberLimit(10)
{
	for (size_t i = 0; i < MODE_NB ; i++)
		_mode[i] = false;
};

Channel::~Channel(){};

const bool	*Channel::getMode()
{
	return (_mode);
}

const std::string Channel::getName()
{
	return (_name);
}

size_t Channel::getMemberNb()
{
	return (_memberNb);
}

const std::vector<Client>	Channel::getMemberList()
{
	return (_memberList);
}

void	Channel::addMember(Client &client)
{
	if (_memberNb == _memberLimit)
		throw ChannelLimitExcedeedException();
	_memberList.push_back(client);
}

bool	Channel::isChannelMember(std::string nickname)
{
	for (size_t i = 0; i < _memberList.size(); i++)
	{
		if (_memberList[i].getNickname() == nickname)
			return (true);
	}
	return (false);
}

void	Channel::displayMode(Client &client)
{
	const std::string array[MODE_NB] = {"t", "i", "k", "o", "l"};
	std::string modes = " :+";
	for (size_t i = 0; i < MODE_NB; i++)
	{
		if (_mode[i])
			modes += array[i];
	}
	std::string msg = ":" + Server::getInstance().getHostname() + " 324 " + client.getNickname() + " " +_name + modes + " \r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
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

bool	paramFlag(char flag)
{
	return (flag == 'o' || flag == 'k' || flag == 'l');
}

bool	strIsAlpha(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isalpha(str[i]))
			return (false);
	}
	return (true);
}

bool	strIsDigit(std::string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}

int Channel::setModeParam(char flag, std::vector<std::string> paramArg, bool disable, size_t id)
{
	if (!paramFlag(flag))
		return (0);
	if (flag == 'l')
	{
		if (disable)
		{
			return (0);
		}
		if (paramArg.size() <= 2)
			return (WPARAM);
		if (!strIsDigit(paramArg[id]))
			return (ERROR);
		_memberLimit = atoi(paramArg[id].c_str());
	}
	else if (flag == 'k')
	{
		if (disable)
		{
			_keyword = "";
		}
		else 
			_keyword = paramArg[id];
	}
	return (0);
	/*else if (flag == 'o')
	{
		
	}*/
}

void	Channel::changeMode(Client client, std::string flags, bool disable, std::string chanName, std::vector<std::string> paramArg)
{
	size_t mode;
	std::string sign = " :+";
	std::string param;
	size_t paramId = 2;
	std::string	msg;
	
	if (disable)
		sign = " :-";
	for (size_t i = 0; i < flags.size(); i++)
	{
		mode = selectMode(flags[i]);
		if (disable)
		{
			if (_mode[mode])
			{
				if (setModeParam(flags[i], paramArg, disable, paramId) < 0)
					continue ;
				_mode[mode] = false;
				param += flags[i];
			}
		}
		else
		{
			if (!_mode[mode])
			{
				_mode[mode] = true;
				if (setModeParam(flags[i], paramArg, disable, paramId) < 0)
					continue ;
				param += flags[i];
			}
		}
	}
	if (param.size() > 0)
	{
		if (paramArg.size() <= 2)
			msg = ":" + client.getNickname() + "!" + client.getUsername() + Server::getInstance().getHostname() + " MODE " + chanName + sign + param + "\r\n";
		else
			msg = ":" + client.getNickname() + "!" + client.getUsername() + Server::getInstance().getHostname() + " MODE " + chanName + sign + param + " :" + paramArg[paramId] + "\r\n";
		send(client.getClientFd(), msg.c_str(), msg.size(), 0);
	}
}
