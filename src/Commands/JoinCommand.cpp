#include <JoinCommand.hpp>
#include <Server.hpp>

JoinCommand::JoinCommand()
{

}

JoinCommand::~JoinCommand()
{

}

std::string	cutChannelName(std::string channelName)
{
	for (size_t i = 0; i < channelName.size(); i++)
	{
		if (channelName[i] == ',')
			return (channelName.substr(0, i));
	}
	return (channelName);
}

bool	reservedChannels(std::string chanName)
{
	std::string rooms[3] = {"#TAVERN", "#ROOM1", "#ROOM2"};
	
	for (size_t i = 0; i < 3; i++)
	{
		if (chanName == rooms[i])
			return (true);
	}
	return (false);
}

void	isValidChannel(Client client, std::string channelName)
{
	if (reservedChannels(channelName))
		throw CustomErrorException(client);
	if (channelName.size() > 50 || !checkPrefix(channelName) || channelName.size() < 2)
		throw InvalidChannelException(client);
}

void	invitedChannel(std::string chanName, Client client)
{
	if (Server::getInstance().checkChannelMode(chanName, i, true))
	{
		if (!Server::getInstance().isInvitedInChannel(client, chanName))
			throw InviteOnlyException(client);
	}
}

void	keyChannel(std::string chanName, Client client, const std::vector<std::string>& arg)
{
	std::string key;

	if (Server::getInstance().checkChannelMode(chanName, k, true))
	{
		if (arg.size() < 2)
			throw IncorrectKeyException(client);
		key = arg[1];
		if (!Server::getInstance().checkChannelKey(chanName, key))
		{
			throw IncorrectKeyException(client);
		}
	}
}

void	JoinCommand::execCmd(Client & emitter, const std::vector<std::string>& arg)
{
	std::string chanName;
	try
	{
		isValidChannel(emitter, arg[0]);
		chanName = cutChannelName(arg[0]);
		{
			if (Server::getInstance().existChannel(chanName))
			{
				if (Server::getInstance().isInChannel(emitter, chanName))
					throw AlreadyInChannelException(emitter);
				invitedChannel(chanName, emitter);
				keyChannel(chanName, emitter, arg);
				Server::getInstance().addChannelMember(emitter, chanName);
			}
			else
				Server::getInstance().createChannel(emitter, chanName);
		}
	}
	catch(std::exception &e)
	{
		sendException(emitter.getClientFd(), e);
	}
}
