#include <Channel.hpp>
#include <Server.hpp>

Channel::Channel(std::string name) : _name(name), _memberNb(0), _memberLimit(10)
{
	for (size_t i = 0; i < MODE_NB ; i++)
		_mode[i] = false;
};

Channel::~Channel(){};

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

void	Channel::changeMode(Client &emitter, const std::vector<std::string>& arg)
{
	(void)emitter;
	(void)arg;
	for(size_t i = 0; i < arg.size(); i++)
	{
		
	}
}
