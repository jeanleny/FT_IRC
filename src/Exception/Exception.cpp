#include <Exception.hpp>

const char *WrongServPassException::what() const throw ()
{
	return ("The password must be less than 60 character long");
}

const char *PortFailedException::what() const throw ()
{
	return ("These port are not available : \n Please select a port meant for IRC (6667 - 6697)\n Or an ephemere port (49185 - 65535)");
}

const char *AddrinfoFailedException::what() const throw ()
{
	return ("Error : Addrinfo call failed");
}

const char *ListenFailedException::what() const throw ()
{
	return ("Error : Listen call failed");
}

const char *SocketFailedException::what() const throw ()
{
	return ("Error : Socket call failed");
}

const char *BindFailedException::what() const throw ()
{
	return ("Error : Bind call failed\n");
}

const char *RecvFailedException::what() const throw()
{
	return ("Error : recv call failed\n");
}


CustomErrorException::CustomErrorException(Client & client)
{
	/*
	_msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " ";
	*/
	if (client.getCommandId() == USER && client.getRegisterStatus() == USER_STATUS)
		_msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :Erroneus Username\r\n";
	else if (client.getRegisterStatus() == PASS_STATUS)
        _msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " :Please enter password (PASS command)\r\n";
	else if (client.getRegisterStatus() == USER_STATUS)
        _msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " :Please enter a username (USER command)\r\n";
    else if (client.getRegisterStatus() == NICK_STATUS)
        _msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " :Please enter a nickname (NICK Command)\r\n";
	else
		_msg = ":" + Server::getInstance().getHostname() + " 400 " + client.getNickname() + " :Too many parameters\r\n";
}

NoSuchNicknameException::NoSuchNicknameException(Client & client)
{
	if (client.getCommandId() == KICK)
		_msg = ":" + Server::getInstance().getHostname() + " 401 " + client.getNickname() + " " + client.getCommandArgs()[1] + " :No such nickname\r\n";
	else
		_msg = ":" + Server::getInstance().getHostname() + " 401 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :No such nickname\r\n";
}

NoSuchChannelException::NoSuchChannelException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 403 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :No such channel\r\n";
}

CannotSendToChannelException::CannotSendToChannelException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 404 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :Cannot send to this channel\r\n";
}

NoRecipientException::NoRecipientException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 411 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :No recipient given\r\n";
}

UnknownCommandException::UnknownCommandException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 421 " + client.getNickname() + " " + client.getCmd() + " :Unknown Command\r\n";
}

NoTextToSendException::NoTextToSendException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 412 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :No text to send\r\n";
}

ErroneusNicknameException::ErroneusNicknameException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 432 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :Erroneus Nickname\r\n";
}

UsedNicknameException::UsedNicknameException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 433 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :Already used nickname\r\n";
}

UserNotInChannelException::UserNotInChannelException(Client & client)
{
	if (client.getCommandId() == KICK)
		_msg = ":" + Server::getInstance().getHostname() + " 441 " + client.getNickname() + " " + client.getCommandArgs()[1] + " :User is not in channel\r\n";
	else
		_msg = ":" + Server::getInstance().getHostname() + " 441 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :User is not in channel\r\n";
}

NotInThisChannelException::NotInThisChannelException(Client & client)
{
	if (client.getCommandId() == PART)
		_msg = ":" + Server::getInstance().getHostname() + " 442 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :You are not in this channel\r\n";
	else
		_msg = ":" + Server::getInstance().getHostname() + " 442 " + client.getNickname() + " " + client.getCommandArgs()[1] + " :You are not in this channel\r\n";
}

AlreadyInChannelException::AlreadyInChannelException(Client & client)
{
	if (client.getCommandId() == JOIN)
	{
		_msg = ":" + Server::getInstance().getHostname() + " 443 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :Is already in channel\r\n";
	}
	else
	{
		_msg = ":" + Server::getInstance().getHostname() + " 443 " + client.getNickname() + " " + client.getCommandArgs()[0] 
			+ " " +  client.getCommandArgs()[1] + " :Is already in channel\r\n";
	}
}

NotEnoughParametersException::NotEnoughParametersException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 461 " + client.getNickname() + " " + client.getCmd() + " :Not enough parameters\r\n";
}

AlreadyRegisteredException::AlreadyRegisteredException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 462 " + client.getNickname() + " :Already Registered\r\n";
}


PasswordMismatchException::PasswordMismatchException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 464 " + client.getNickname() + " :Incorrect Password\r\n";
}

ChannelLimitExcedeedException::ChannelLimitExcedeedException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 471 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :Cannot join channel (channel is full)\r\n";
}
	
InviteOnlyException::InviteOnlyException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 473 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :This channel is on invite only mode\r\n";
}

IncorrectKeyException::IncorrectKeyException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 475 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :Incorrect channel key\r\n";
}

InvalidChannelException::InvalidChannelException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 476 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :Invalid channel name\r\n";
}

NotAnOperatorException::NotAnOperatorException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 482 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :You need to be an operator\r\n";
}



