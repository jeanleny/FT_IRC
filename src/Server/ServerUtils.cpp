#include "Server.hpp"

void	Server::entryParsing(std::string password, std::string portEntry)
{
	size_t port = atoi(portEntry.c_str());
	if (password.size() > 60)
		throw WrongServPassException();
	if (port == 6667 || port == 6697 || (port >= 49185 && port <= 65535))
		return ;
	throw PortFailedException();
}

bool	Server::isRegisterCommand(ssize_t cmdId)
{
	if (cmdId == USER || cmdId == NICK || cmdId == PASS)
		return (true);
	return (false);
}

bool	Server::isCommandFromGame(std::string chanName)
{
	std::string rooms[3] = {"#LOBBY", "#ROOM1", "#ROOM2"};

	for (size_t i = 0; i < 3; i++)
	{
		if (chanName == rooms[i])
			return true;
	}
	return false;
}

void	Server::sendWelcomeMessage(Client & client)
{
	std::string msg = ":" + Server::getInstance().getHostname() + " 001 " + client.getNickname() 
        + " :Welcome to the Internet Relay Network " + client.getNickname() + "!" + client.getUsername() + "@localhost\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

void	Server::sendPassQuery(Client & client)
{
	std::string	msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " :Please enter password (PASS command)\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

void	Server::sendUserQuery(Client & client)
{
	std::string	msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " :Please enter a username (USER command)\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

void	Server::sendNickQuery(Client & client)
{
	std::string	msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " :Please enter a nickname (NICK command)\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}


void	Server::sendNickMessage(Client & client)
{
	std::string msg = ":" + client.getOldNickname() + "!" + client.getUsername() + "@localhost" + " NICK :" + client.getNickname() + "\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);

	std::string	chanName;
	for (size_t i = 0; i < _channels.size(); i++)
	{
		chanName = _channels[i].getName();
		if (isInChannel(client, chanName))
			sendMessageToChannel(client, chanName, msg.c_str());
	}
}

bool	Server::isInServer(Client &client)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (client.getClientFd() == _clients[i].getClientFd())
			return (true);
	}
	return (false);
}

void	Server::serverClosing()
{
	if (g_exit)
	{
		for (size_t i = 0; i < _clientsFds.size(); i++)
			close(_clientsFds[i]);
	}
	close(_servFd);
	close(_epollFd);
}
