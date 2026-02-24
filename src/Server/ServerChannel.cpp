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

bool	Server::checkChannelOperator(std::string chanName, Client client)
{
	return (_channels[getChannelByName(chanName)].checkOperator(client));
}

void	Server::addChannelOperator(std::string chanName, Client target)
{
	_channels[getChannelByName(chanName)].addOperator(target);
}

void	Server::rmChannelOperator(std::string chanName, Client target)
{
	_channels[getChannelByName(chanName)].rmOperator(target);
}

bool	Server::checkChannelKey(std::string chanName, std::string key)
{
	return (_channels[getChannelByName(chanName)].checkKey(key));
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

bool	Server::isInChannel(Client &client, std::string chanName)
{
	for(size_t i = 0; i < _channels.size(); i++)
	{
		if (_channels[i].getName() == chanName)
		{
			if (_channels[i].isChannelMember(client.getClientFd()))
				return (true);
		}
	}
	return (false);
}

bool	Server::isInvitedInChannel(Client &client, std::string chanName)
{
	size_t id = getChannelByName(chanName);
	Channel	chan = _channels[id];

	if (chan.isInvited(client.getClientFd()))
		return true;
	return (false);
}

void	Server::addChannelMember(Client &client, std::string chanName)
{
	ssize_t id = getChannelByName(chanName);
	
	_channels[id].addMember(client);
	sendJoinMessage(client, chanName);
}

void	Server::removeChannelMember(Client &client, std::string chanName)
{
	ssize_t id = getChannelByName(chanName);
	
	std::string	msg = ":" + client.getNickname() + "!" + client.getUsername() + "@" + getHostname() 
		+ " PART " + chanName + "\r\n";
	sendMessageToChannel(client, chanName, msg.c_str());

	_channels[id].removeMember(client);
	if (_channels[id].getMemberNb() == 0)
		_channels.erase(_channels.begin() + id);

}


void	Server::kickChannelMember(Client & client, Client &kicked, std::string chanName)
{
	ssize_t id = getChannelByName(chanName);
	
	std::string	msg = ":" + client.getNickname() + "!" + client.getUsername() + "@" + getHostname() 
	+ " KICK " + chanName + " " + kicked.getNickname() + " :" + client.getNickname() + "\r\n";
	sendMessageToChannel(client, chanName, msg.c_str());
	
	_channels[id].removeMember(kicked);
}

void	Server::inviteChannelMember(Client & client, Client &invited, std::string chanName)
{
	ssize_t id = getChannelByName(chanName);
	
	std::string	msg = ":" + client.getNickname() + "!" + client.getUsername() + "@" + getHostname() 
	+ " INVITE " + invited.getNickname() + " :" + chanName + "\r\n";
	sendMessageToChannel(client, chanName, msg.c_str());
	send(invited.getClientFd(), msg.c_str(), msg.size(), 0);
	
	_channels[id].inviteMember(invited);
}

void	Server::createChannel(Client & emitter, std::string chanName)
{
	Channel	obj(chanName);
	ssize_t id;

	_channels.push_back(obj);
	id = getChannelByName(chanName);
	_channels[id].addMember(emitter);
	_channels[id].addOperator(emitter);
	sendJoinMessage(emitter, chanName);
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
		if (clientFd == client.getClientFd() && (client.getCommandId() == PRIVMSG || client.getCommandId() == NICK))
			continue ;
		send(clientFd, msg, len, MSG_NOSIGNAL);
	}
}

void	Server::displayChannelTopic(Client & client, std::string chanName)
{
	int	id = getChannelByName(chanName);

	_channels[id].displayTopic(client);
}

void	Server::changeChannelTopic(Client & client, std::string chanName, std::string newTopic)
{
	int	id = getChannelByName(chanName);

	_channels[id].changeTopic(client, newTopic);
}

void	Server::sendJoinMessage(Client &emitter, std::string & chanName)
{
	size_t 				index = getChannelByName(chanName);
	std::string			topic = _channels[index].getTopic();
	
	std::string msg = ":" + emitter.getNickname() + "!" + emitter.getUsername() + "@" + getHostname() + " JOIN " + chanName + "\r\n";
	msg += ":" + getHostname() + " 332 " + emitter.getNickname() +" " + chanName + " :" + topic + "\r\n";
	msg += ":" + getHostname() + " 353 " + emitter.getNickname() +" = " + chanName + " :" + _channels[index].buildList() + "\r\n";
	msg += ":" + getHostname() + " 366 " + emitter.getNickname() +" " + chanName + " :End of /NAMES list\r\n";
	
	sendMessageToChannel(emitter, chanName, msg.c_str());
}

void	Server::changeChannelNickList(Client client)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (isInChannel(client, _channels[i].getName()))
			_channels[i].changeNickList(client);
	}
}
