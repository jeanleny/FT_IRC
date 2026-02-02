#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <iostream>
#include "Client.hpp"
#include "Server.hpp"

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

class PasswordQueryException : public std::exception
{
	public :
		const char * what() const throw();
};

class UsernameQueryException : public std::exception
{
	public :
		const char * what() const throw();
};

class NicknameQueryException : public std::exception
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

class UnvalidPasswordException : public std::exception
{
	public :
		const char * what() const throw();
};

class MissingArgumentsException : public std::exception
{
	public :
		const char * what() const throw();
};

class ErroneusNicknameException : public std::exception
{
	public :

		ErroneusNicknameException(Client & client);
		virtual ~ErroneusNicknameException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class UsedNicknameException : public std::exception
{
	public :

		UsedNicknameException(Client & client);
		virtual ~UsedNicknameException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class ErroneusUsernameException : public std::exception
{
	public :
		const char * what() const throw();
};

class InvalidChannelException : public std::exception
{
	public :

		InvalidChannelException(Client & client);
		virtual ~InvalidChannelException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :
		std::string	_msg;
};

class AlreadyInChannelException : public std::exception
{
	public :
		const char * what() const throw();
};

class ChannelLimitExcedeedException : public std::exception
{
	public :
		const char * what() const throw();
};

class NoSuchChannelException : public std::exception
{
	public :

		NoSuchChannelException(Client & client);
		virtual ~NoSuchChannelException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

class NotEnoughParametersException : public std::exception
{
	public :

		NotEnoughParametersException(Client & client);
		virtual ~NotEnoughParametersException() throw() {}
		const char * what() const throw() {return _msg.c_str();}

	private :

		std::string	_msg;
};

#endif
