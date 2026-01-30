#include "ServerUtils.h"

bool	isRegisterCommand(ssize_t cmdId)
{
	if (cmdId == USER || cmdId == NICK || cmdId == PASS)
		return (true);
	return (false);
}

void	Server::sendWelcomeMessage(Client & client)
{
	std::string msg = ":" + Server::getInstance().getHostname() + " 001 " + client.getNickname() 
        + " :Welcome to the Internet Relay Network " + client.getNickname() + "!" + client.getUsername() + "@localhost\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}

void	Server::sendNickMessage(Client & client)
{
	std::string msg = ":" + client.getOldNickname() + "!" + client.getUsername() + "@localhost" + " NICK :" + client.getNickname() + "\r\n";
	send(client.getClientFd(), msg.c_str(), msg.size(), 0);
}



