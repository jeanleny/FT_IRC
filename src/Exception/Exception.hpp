#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <iostream>

class AddrinfoFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class BindFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class SocketFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class ListenFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class RecvFailedException : public std::exception
{
	public :
		const char * what() const throw();
};

class RegisterQueryException : public std::exception
{
	public :
		const char * what() const throw();
};

class AlreadyRegisteredException : public std::exception
{
	public :
		const char * what() const throw();
};

class WrongCommandException : public std::exception
{
	public :
		const char * what() const throw();
};

#endif
