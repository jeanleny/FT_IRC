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
        + " " + client.getNickname() + "!" + client.getUsername() + "@localhost\r\n";
}

UsedNicknameException::UsedNicknameException(Client & client)
{
	_msg = ":" + Server::getInstance().getHostname() + " 433 " + client.getNickname() + " " + client.getCommandArgs()[0] 
        + " " + client.getNickname() + "!" + client.getUsername() + "@localhost\r\n";
}


const char *ErroneusUsernameException::what() const throw()
{
	return ("Error : Erroneus Username\n");
}

const char *InvalidChannelException::what() const throw()
{
	//476
	return ("Error : Invalid channel name\n");
}
