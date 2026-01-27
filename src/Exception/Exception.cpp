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
