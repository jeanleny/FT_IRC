#include <JoinCommand.hpp>
#include <Server.hpp>

JoinCommand::JoinCommand()
{

}

JoinCommand::~JoinCommand()
{

}

bool	checkPrefix(std::string channelName)
{
	return (channelName[0] == '#');
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

void	isValidChannel(std::string channelName)
{
	if (channelName.size() > 50 || !checkPrefix(channelName))
		throw InvalidChannelException();
}


void	JoinCommand::execCmd(Client & emitter, const std::vector<std::string>& arg)
{
	std::string chanName;

	for (size_t i = 0; i < arg.size(); i++)
	{
		try
		{
			isValidChannel(arg[i]);
			chanName = cutChannelName(arg[i]);
			{
				if (Server::getInstance().findChannel(chanName))
				{
					if (Server::getInstance().isInChannel(emitter, chanName))
						throw AlreadyInChannelException();
					Server::getInstance().addChannelMember(emitter, chanName);
				}
				else
				{
					Server::getInstance().createChannel(emitter, chanName);
					Server::getInstance().addChannelMember(emitter, chanName);
				}
			}
		}
		catch(std::exception &e)
		{
			sendException(emitter.getClientFd(), e);
		}
	}
}
