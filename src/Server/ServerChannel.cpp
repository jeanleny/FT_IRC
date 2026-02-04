#include <Server.hpp>

void	Server::displayChannelMode(Client emitter, std::string arg)
{
	_channels[getChannelByName(arg)].displayMode(emitter);
}

void	Server::changeChannelMode(std::string chanName, size_t mode, bool state)
{
	_channels[getChannelByName(chanName)].changeMode(mode, state);
}

void	Server::changeChannelKey(std::string chanName, std::string key)
{
	_channels[getChannelByName(chanName)].changeKey(key);
}

void	Server::changeChannelLimit(std::string chanName, size_t limit)
{
	_channels[getChannelByName(chanName)].changeLimit(limit);
}

bool	Server::checkChannelMode(std::string chanName, size_t mode, bool state)
{
	return (_channels[getChannelByName(chanName)].checkMode(mode, state));
}

ssize_t	Server::getChannelByName(std::string chanName)
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == chanName)
		{
			return (i);
		}
	}
	return (-1);
}

bool	Server::existChannel(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (name == _channels[i].getName())
			return (true);
	}
	return (false);
}

bool	Server::isInChannel(Client &client, std::string name)
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == name)
		{
			if (_channels[i].isChannelMember(client.getClientFd()))
				return (true);
		}
	}
	return (false);
}

void	Server::addChannelMember(Client &client, std::string chanName)
{
	ssize_t id = getChannelByName(chanName);
	
	_channels[id].addMember(client);
}

void	Server::createChannel(Client & emitter, std::string chanName)
{
	Channel	obj(chanName);
	std::string msg = ":" + emitter.getNickname() + "!" + emitter.getUsername() + "@" + getHostname() + " JOIN " + chanName + "\r\n";
	std::string msg2 = ":" + getHostname() + " 332 " + emitter.getNickname() +" " + chanName + " :topic\r\n";
	std::string msg3 = ":" + getHostname() + " 353 " + emitter.getNickname() +" = " + chanName + " :" + "@" + emitter.getNickname() + "\r\n";
	std::string msg4 = ":" + getHostname() + " 366 " + emitter.getNickname() +" " + chanName + " :End of /NAMES list\r\n";

	_channels.push_back(obj);
	send(emitter.getClientFd(), msg.c_str(), msg.size(), 0);
	send(emitter.getClientFd(), msg2.c_str(), msg2.size(), 0);
	send(emitter.getClientFd(), msg3.c_str(), msg3.size(), 0);
	send(emitter.getClientFd(), msg4.c_str(), msg4.size(), 0);
}

void	Server::sendMessageToChannel(Client & client, std::string & chanName, const char *msg)
{
	size_t 				index = getChannelByName(chanName);
	Channel				chan = _channels[index];
	std::vector<Client>	memberList = chan.getMemberList();
	int					clientFd;
	int 				len = strlen(msg);

	for (size_t i = 0; i < memberList.size(); i++)
	{
		clientFd = memberList[i].getClientFd();
		if (clientFd == client.getClientFd())
			continue ;
		send(clientFd, msg, len, 0);
	}
}
