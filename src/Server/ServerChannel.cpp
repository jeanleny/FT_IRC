#include <Server.hpp>

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
