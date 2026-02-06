#include <Exception.hpp>

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

const char *RegisterQueryException::what() const throw()
{
	return ("Error : Please register yourself\n");
}

const char *PasswordQueryException::what() const throw()
{
	return ("Error : Please enter the password\n");
}

const char *UsernameQueryException::what() const throw()
{
	return ("Error : Please enter your username\n");
}

const char *NicknameQueryException::what() const throw()
{
	return ("Error : Please enter your nickname\n");
}

const char *AlreadyRegisteredException::what() const throw()
{
	return ("Error : You are already authenticate\n");
}

const char *WrongCommandException::what() const throw()
{
	return ("Error : Please enter a valid command\n");
}

const char *UnvalidPasswordException::what() const throw()
{
	return ("Error : Unvalid Password\n");
}

const char *MissingArgumentsException::what() const throw()
{
	return ("Error : This command needs at least one argument\n");
}

ErroneusNicknameException::ErroneusNicknameException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 432 " + client.getNickname() + " " + client.getCommandArgs()[0] 
        + " :Erroneus Nickname\r\n";
}

UsedNicknameException::UsedNicknameException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 433 " + client.getNickname() + " " + client.getCommandArgs()[0] 
        + " :Already used nickname\r\n";
}
UserNotInChannelException::UserNotInChannelException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 441 " + client.getNickname() + " " + client.getCommandArgs()[1] 
        + " :User is not in channel\r\n";
}

NotInThisChannelException::NotInThisChannelException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 442 " + client.getNickname() + " " + client.getCommandArgs()[1] 
        + " :You are not in this channel\r\n";
}

AlreadyInChannelException::AlreadyInChannelException(Client & client)
{
	// :chatjunkies.org 443 tobourge2 peris #truite :is already on channel

	_msg = ":" + Server::getInstance().getHostname() + " 443 " + client.getNickname() + " " + client.getCommandArgs()[0] 
        + " " +  client.getCommandArgs()[1] + " :Is already in channel\r\n";
}

NoRecipientException::NoRecipientException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 411 " + client.getNickname() + " " + client.getCommandArgs()[0] 
        + "  :No recipient given\r\n";
}

NoTextToSendException::NoTextToSendException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 412 " + client.getNickname() + " " + client.getCommandArgs()[0] 
        + "  :No text to send\r\n";
}

CannotSendToChannelException::CannotSendToChannelException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 404 " + client.getNickname() + " " + client.getCommandArgs()[0] 
        + "  :Cannot send to this channel\r\n";
}

NoSuchNicknameException::NoSuchNicknameException(Client & client)
{
	if (client.getCommandId() == KICK)
		_msg = ":" + Server::getInstance().getHostname() + " 401 " + client.getNickname() + " " + client.getCommandArgs()[1] + "  :No such nickname\r\n";
	else
		_msg = ":" + Server::getInstance().getHostname() + " 401 " + client.getNickname() + " " + client.getCommandArgs()[0] + "  :No such nickname\r\n";
}

const char *ErroneusUsernameException::what() const throw()
{
	return ("Error : Erroneus Username\n");
}

InvalidChannelException::InvalidChannelException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 476 " + client.getNickname() + " " + client.getCommandArgs()[0] + ":Invalid channel name\r\n";
}
NotAnOperatorException::NotAnOperatorException(Client & client)
{
    _msg = ":" + Server::getInstance().getHostname() + " 482 " + client.getNickname() + " " + client.getCommandArgs()[0] + "  :You need to be an operator\r\n";
}


const char *ChannelLimitExcedeedException::what() const throw()
{
	return ("Error : Channel limit user reached\n");
}

NoSuchChannelException::NoSuchChannelException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 403 " + client.getNickname() + " " + client.getCommandArgs()[0] + " :No such channel\r\n";
}

NotEnoughParametersException::NotEnoughParametersException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 461 " + client.getNickname() + " " + client.getCmd() + " :Not enough parameters\r\n";
}
