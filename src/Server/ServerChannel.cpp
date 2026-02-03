#include <Server.hpp>

void	Server::displayChannelMode(Client emitter, std::string arg)
{
	_channels[getChannelByName(arg)].displayMode(emitter);
}

void	Server::changeChannelMode(Client emitter, const std::vector<std::string>& arg)
{
	_channels[getChannelByName(arg[0])].changeMode(emitter, arg);
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
			if (_channels[i].isChannelMember(client.getNickname()))
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

	std::cout << "msg : " << msg << std::endl;
	for (size_t i = 0; i < memberList.size(); i++)
	{
		clientFd = memberList[i].getClientFd();
		if (clientFd == client.getClientFd())
			continue ;
		send(clientFd, msg, len, 0);
	}
}
