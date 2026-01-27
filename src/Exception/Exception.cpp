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
	return ("Error : Bind call failed");
}

const char *RecvFailedException::what() const throw()
{
	return ("Error : recv call failed");
}

const char *RegisterQueryException::what() const throw()
{
	return ("Error : Please register yourself");
}

const char *AlreadyRegisteredException::what() const throw()
{
	return ("Error : You are already authenticate");
}

const char *WrongCommandException::what() const throw()
{
	return ("Error : Please enter a valid command");
}
