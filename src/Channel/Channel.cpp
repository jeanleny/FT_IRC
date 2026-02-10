#include <Channel.hpp>
#include <Server.hpp>

Channel::Channel(std::string name) : _name(name), _topic("No topic is set"), _memberNb(0), _memberLimit(0)
{
	for (size_t i = 0; i < MODE_NB ; i++)
		_mode[i] = false;
};

Channel::~Channel(){};

const std::string Channel::getName()
{
	return (_name);
}

const std::string	Channel::getList()
{
	return (_list);
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
	if (checkMode(l, true))
	{
		if (_memberNb >= _memberLimit)
			throw ChannelLimitExcedeedException(client);
	}
	_memberList.push_back(client);
	_memberNb++;
	_list += " ";
	_list += client.getNickname();
}

void	Channel::inviteMember(Client &client)
{
	for (size_t i = 0;  i < _invitedList.size(); i++)
	{
		if(client.getClientFd() == _invitedList[i])
			return ;
	}
	_invitedList.push_back(client.getClientFd());
}

void	Channel::removeInvitedMember(Client &client)
{
	for (size_t i = 0;  i < _invitedList.size(); i++)
	{
		if(client.getClientFd() == _invitedList[i])
			break ;
	}
	_invitedList.erase(_invitedList.begin() + i);
}

void	Channel::removeFromListString(Client & client)
{
	std::string	nick = client.getNickname();
	size_t pos = _list.find(nick);
	
	if (pos == std::string::npos)
		return ;
	
	_list.erase(pos - 1, nick.size() + 1);
}

void	Channel::removeMember(Client &client)
{
	for (size_t i = 0;  i < _memberList.size(); i++)
	{
		if(client.getClientFd() == _memberList[i].getClientFd())
			break ;
	}
	_memberList.erase(_memberList.begin() + i);
	_memberNb -= 1;
	removeFromListString(client);
	if (isInvited(client.getClientFd()))
		removeInvitedMember(client);
	if (checkOperator(client))
		rmOperator(client);
}

bool	Channel::isChannelMember(int fd)
{
	for (size_t i = 0; i < _memberList.size(); i++)
	{
		if (_memberList[i].getClientFd() == fd)
			return (true);
	}
	return (false);
}

bool	Channel::isInvited(int fd)
{
	for (size_t i = 0; i < _invitedList.size(); i++)
	{
		if (fd == _invitedList[i])
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

void	Channel::displayTopic(Client &client)
{
	std::string	msg;
	if (_topic == "No topic is set")
	{
		msg = ":" + Server::getInstance().getHostname() + " 331 " + client.getNickname() + " " + _name 
        	+ " :" + _topic + "\r\n";
	}
	else
	{
		msg = ":" + Server::getInstance().getHostname() + " 332 " + client.getNickname() + " " + _name 
        	+ " :" + _topic + "\r\n";
	}
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

void	Channel::changeTopic(Client & client, std::string newTopic)
{
	if (newTopic == _topic)
		return ;

	_topic = newTopic;

	std::string	msg = ":" + client.getNickname() + "!" + client.getUsername() + "@" + Server::getInstance().getHostname() 
		+ " TOPIC " + _name + " :" + newTopic + "\r\n";;
	Server::getInstance().sendMessageToChannel(client, _name, msg.c_str());
}

void	Channel::changeKey(std::string key)
{
	_keyword = key;
}

void	Channel::changeLimit(size_t limit)
{
	_memberLimit = limit;
}

void	Channel::changeMode(size_t mode, bool disable)
{
	if (mode == o)
		return;
	if (disable)
		_mode[mode] = false;
	else
		_mode[mode] = true;
}

bool	Channel::checkMode(size_t mode, bool state)
{
	if (mode == o)
		return (true);
	return (_mode[mode] == state);
}

bool	Channel::checkOperator(Client client)
{
	for (size_t i = 0; i < _operators.size(); i++)
	{
		if (client.getClientFd() == _operators[i])
			return (true);
	}
	return (false);
}

bool	Channel::checkKey(std::string key)
{
	return (key == _keyword);
}

void	Channel::addOperator(Client target)
{
	_operators.push_back(target.getClientFd());
}

void	Channel::rmOperator(Client target)
{
	int fd = target.getClientFd();
	std::vector<int>::iterator pos = find(_operators.begin(), _operators.end(), fd);
	_operators.erase(pos);
}
